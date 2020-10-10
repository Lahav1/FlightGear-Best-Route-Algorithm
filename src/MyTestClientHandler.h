#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

template <class P, class S>

class MyTestClientHandler : public ClientHandler<P, S> {
private:
    Solver<P, S>* solver;
    CacheManager<P, S>* cacheManager;

public:
    MyTestClientHandler(Solver<P, S>* s, CacheManager<P, S>* cm) {
        this->solver = s;
        this->cacheManager = cm;
    }

    void handleClient(int sockfd) {
        while(1) {
            int n = 0;
            char message[256];
            bzero(message, 256);
            n = read(sockfd, message, 255);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            if(Lexer::charPtrToString(message) == "end\r\n") {
                return;
            }
            char* solution = Lexer::stringToCharPtr(this->getSolution(message));
            // send the message to the server.
            n = (int) write(sockfd, solution, strlen(solution));
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
    }

    S getSolution(P problem) {
        pair<string, string> p = this->cacheManager->getSolverTypes();
        string problemType = p.first;
        string solutionType = p.second;
        if ((problemType == "string") && (solutionType == "string")) {
            problem = Lexer::removeWhiteSpaces(problem);
            S solution;
            if (this->cacheManager->isSaved(problem)) {
                solution = this->cacheManager->findSolution(problem);
            } else {
                solution = this->solver->solve(problem);
                this->cacheManager->addNewSolution(problem, solution);
            }
            return solution;
        }
//        return this->solver->solve(problem);
    }
};

#endif //MILESTONE2_MYTESTCLIENTHANDLER_H
