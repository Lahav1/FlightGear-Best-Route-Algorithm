#ifndef MILESTONE2_MYCLIENTHANDLER_H
#define MILESTONE2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Point.h"
#include "MatrixNode.h"
#include "Matrix.h"
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>

template <class P, class S>

class MyClientHandler : public ClientHandler<P, S> {
private:
    Solver<P, S>* solver;
    CacheManager<P, S>* cacheManager;

public:
    /****************************************************
    * Function Name:            MyClientHandler.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    MyClientHandler(Solver<P, S>* s, CacheManager<P, S>* cm) {
        this->solver = s;
        this->cacheManager = cm;
    }

    /****************************************************
    * Function Name:            handleClient.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void handleClient(int sockfd) {
        vector<string> block = {};
        while(1) {
            int n = 0;
            char message[4096];
            bzero(message, 4095);
            n = read(sockfd, message, 4096);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            string strMsg = Lexer::charPtrToString(message);
            string end = "end\r\n";
            if (strMsg.find(end) != std::string::npos) {
                char* solution = Lexer::stringToCharPtr(this->getSolution(block));
                // send the message to the server.
                n = (int) write(sockfd, solution, strlen(solution));
                if (n < 0) {
                    perror("ERROR writing to socket");
                    exit(1);
                }
                delete[](solution);
                return;
            }
            block.push_back(Lexer::charPtrToString(message));
        }
    }

    /****************************************************
    * Function Name:            getSolution.
    * The Input:                vector<string> block.
    * The Output:
    * The Function Operation:
    ****************************************************/
    S getSolution(vector<string> block) {
        block = Lexer::SeaparateBlockByEndline(block);
        pair<string, string> p = this->cacheManager->getSolverTypes();
        string problemType = p.first;
        string solutionType = p.second;
        // if the problem is from "FindShortestPath" type -
        if ((problemType == "matrix") && (solutionType == "string")) {
            int numOfRows = (int) block.size() - 2;
            int numOfCols = (int) Lexer::separateStringByChar(block[0], ',').size();
            vector<vector<State<Point*>*>> v = {};
            for (int i = 0; i < numOfRows; i++) {
                vector<string> current =  Lexer::separateStringByChar(block[i], ',');
                vector<State<Point*>*> temp = {};
                for (int j = 0; j < numOfCols; j++) {
                    Point* p = new Point(j, i);
                    int value = (int) Lexer::stringToDouble(Lexer::removeWhiteSpaces(current[j]));
                    State<Point*>* node = new MatrixNode(p, value);
                    temp.push_back(node);
                }
                v.push_back(temp);
            }
            // add start and goal points.
            vector<string> vstart = Lexer::separateStringByChar(block[block.size() - 2], ',');
            Point* start = new Point (stoi(vstart[1]), stoi(vstart[0]));
            vector<string> vgoal = Lexer::separateStringByChar(block[block.size() - 1], ',');
            Point* goal = new Point (stoi(vgoal[1]), stoi(vgoal[0]));
            Matrix* problem = new Matrix(v, start, goal);
            string solution = "";
            // check if the solution exists in cache manager.
            if (this->cacheManager->isSaved(problem)) {
                solution = this->cacheManager->findSolution(problem);
            } else {
                solution = this->solver->solve(problem);
                solution = Lexer::removeLastChar(solution);
                this->cacheManager->addNewSolution(problem, solution);
            }
            delete(problem);
            return solution;
        }
    }

    /****************************************************
    * Function Name:            destructor.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    ~MyClientHandler() {
        delete(this->solver);
        delete(this->cacheManager);
    }
};

#endif //MILESTONE2_MYCLIENTHANDLER_H
