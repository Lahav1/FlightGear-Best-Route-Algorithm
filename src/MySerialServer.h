#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "Server.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "thread"
#include <string.h>

using namespace server_side;

template <class P, class S> class MySerialServer : public Server<P,S> {
private:
    int sockfd;
    int newsockfd;
    thread* t;

public:
    /****************************************************
    * Function Name:
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    MySerialServer() {
        this->sockfd = 0;
        this->newsockfd = 0;
    }

    /****************************************************
    * Function Name:
    * The Input:
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
        listen(this->sockfd, 5);
        this->t = new thread(&MySerialServer::start, this, c);
        t->join();
    }

    /****************************************************
    * Function Name:
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void start(ClientHandler<P, S>* c) {
        int i = 0;
        while(1) {
            i = 0;
            thread* acc = new thread(&MySerialServer::acceptConnection, this);
            while(i < 10) {
                if(newsockfd > 0) {
                    acc->join();
                    delete(acc);
                    cout << "connected." << endl;
                    c->handleClient(this->newsockfd);
                    ::close(this->newsockfd);
                    this->newsockfd = 0;
                    break;
                } else {
                    cout << i << endl;
                    sleep(1);
                    i++;
                }
            }
            if (i >= 10){
                acc->detach();
                delete(acc);
                break;
            }
        }
        cout << "closing server" << endl;
        closeServer();
    }

    /****************************************************
    * Function Name:
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void acceptConnection() {
        struct sockaddr_in cli_addr;
        int clilen = sizeof(cli_addr);
        // Accept actual connection from the client.
        this->newsockfd = accept(this->sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
        if (this->newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        return;
    }

    /****************************************************
    * Function Name:
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void closeServer() {
        // destructors.
    }
};

#endif //MILESTONE2_MYSERIALSERVER_H