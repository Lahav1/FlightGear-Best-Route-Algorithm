#include "BFS.h"

/****************************************************
* Function Name:            constructor.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
BFS::BFS() {}

/****************************************************
* Function Name:            search.
* The Input:                Matrix* matrix.
* The Output:
* The Function Operation:
****************************************************/
string BFS::search(Matrix* matrix) {
    queue<State<Point*>*> q;
    q.push(matrix->getInitialState());
    vector<State<Point*>*> nodesEvaluated;
    nodesEvaluated.push_back(matrix->getInitialState());

    while(q.size() != 0) {
        State<Point*>* currentState = q.front();
        q.pop();
        if(matrix->isGoal(currentState)) {
            string s = currentState->backTrace(matrix->getStart());
            return s;
        }
        vector<State<Point*>*> possibleStates = matrix->getPossibleStates(currentState);
        for(auto c : possibleStates) {
            bool containChild = false;
            for(auto node : nodesEvaluated) {
                if(c == node) {
                    containChild = true;
                    break;
                }
            }
            if(!containChild) {
                c->setCameFrom(currentState);
                q.push(c);
                nodesEvaluated.push_back(c);
            }
        }
    }
}
