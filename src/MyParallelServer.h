#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H

#include "Server.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "thread"
#include "MyTestClientHandler.h"
#include <string.h>
#include <vector>

using namespace server_side;

template <class P, class S> class MyParallelServer : public Server<P,S> {
private:
    int sockfd;
    int newsockfd;
    mutable int activeConnections;
    vector<pair<thread*, int>> clientThreads;
    vector<thread*> acceptThreads;

public:
     /****************************************************
     * Function Name:           constructor.
     * The Input:
     * The Output:
     * The Function Operation:
     ****************************************************/
    MyParallelServer() {
        this->sockfd = 0;
        this->newsockfd = 0;
        this->activeConnections = 0;
    }

    /****************************************************
    * Function Name:            acceptConnection.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void acceptConnection() {
        struct sockaddr_in cli_addr;
        int clilen = sizeof(cli_addr);
        // accept actual connection from the client.
        this->newsockfd = accept(this->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        if (this->newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        return;
    }

    /****************************************************
    * Function Name:            callClientHandler.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void callClientHandler(ClientHandler<P, S>* c, int sock) {
        // increase active connections number.
        this->activeConnections++;
        // call handle client function.
        c->handleClient(sock);
        // decrease active connections number.
        this->activeConnections--;
    }

    /****************************************************
    * Function Name:            start.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void start(ClientHandler<P, S>* c) {
        int i;
        // wait for the first client for unlimited time.
        struct sockaddr_in cli_addr;
        int clilen = sizeof(cli_addr);
        // accept actual connection from the client.
        this->newsockfd = accept(this->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        if (this->newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        // infinite loop for accepting new clients (until reaching the timeout).
        while(true) {
            sleep(1);
            if(this->activeConnections > 0) {
                // wait for a new client to connect in a background thread.
                thread* acc = new thread(&MyParallelServer::acceptConnection, this);
                this->acceptThreads.push_back(acc);
                // while there are active connections keep letting new clients in.
                while(activeConnections > 0) {
                    if(this->newsockfd > 0) {
                        pair<thread*, int> p;
                        p.second = newsockfd;
                        p.first = new thread(&MyParallelServer::callClientHandler, this, c, newsockfd);
                        this->clientThreads.push_back(p);
                        this->newsockfd = 0;
                        break;
                    }
                }
            }
            // if the number of active connections is 0, start counting before closing the server.
            if(this->activeConnections == 0) {
                i = 0;
                thread* acc = new thread(&MyParallelServer::acceptConnection, this);
                this->acceptThreads.push_back(acc);
                while(i < 1) {
                    if(this->newsockfd > 0) {
                        pair<thread*, int> p;
                        p.second = newsockfd;
                        p.first = new thread(&MyParallelServer::callClientHandler, this, c, newsockfd);
                        this->clientThreads.push_back(p);
                        this->newsockfd = 0;
                        break;
                    } else {
                        sleep(1);
                        i++;
                    }
                }
                if (i >= 1){
                    break;
                }
            }
        }
        // close the server.
        closeServer(c);
    }

    /****************************************************
    * Function Name:            open.
    * The Input:                int port, ClientHandler<P, S>* c.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void open(int port, ClientHandler<P, S>* c) {
        struct sockaddr_in serv_addr;
        // First call to socket() function.
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }
        // Initialize socket structure.
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(port);
        // Now bind the host address using bind() call.
        if (bind(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR on binding");
            exit(1);
        }
        // Now start listening for the clients, here process will
        // go in sleep mode and will wait for the incoming connection.
        listen(this->sockfd, 200);
        this->start(c);
    }

    /****************************************************
    * Function Name:            closeServer.
    * The Input:                ClientHandler<P, S>* c.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void closeServer(ClientHandler<P, S>* c) {
        // delete all of the client threads.
        for (int i = 0; i < this->clientThreads.size(); i++) {
            pair<thread*, int> p = this->clientThreads[i];
            p.first->detach();
            delete(p.first);
            ::close(p.second);
        }
        // delete all accept threads.
        for (int i = 0; i < this->acceptThreads.size(); i++) {
            this->acceptThreads[i]->detach();
            delete(this->acceptThreads[i]);
        }
        // close main socket.
        ::close(this->sockfd);
        // delete client handler to start the destruction loop.
        delete(c);
    }
};

#endif //MILESTONE2_MYPARALLELSERVER_H
