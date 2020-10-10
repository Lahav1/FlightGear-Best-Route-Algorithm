#include "Main.h"

/****************************************************
* Function Name:            main.
* The Input:                argv[1] is the port number.
* The Output:
* The Function Operation:   uses the implementation of a-star as the most efficient algorithm.
****************************************************/
int main(int argc, char* argv[]) {
    int port = stoi(argv[1]);
    FileCacheManager<Matrix*, string>* cm = new FileCacheManager<Matrix*, string>("FindShortestPath");
    Astar* astar = new Astar();
    SolverSearcher<Matrix*, string>* s = new SolverSearcher<Matrix*, string>(astar);
    ClientHandler<Matrix*, string>* ch = new MyClientHandler<Matrix*, string>(s, cm);
    MyParallelServer<Matrix*, string>* server = new MyParallelServer<Matrix*, string>();
    server->open(port, ch);
    delete(server);
    return 0;
}

