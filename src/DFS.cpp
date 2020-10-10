#include "DFS.h"

/****************************************************
* Function Name:            constructor.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
DFS::DFS() {}

/****************************************************
* Function Name:            search.
* The Input:                Matrix* matrix.
* The Output:
* The Function Operation:
****************************************************/
string DFS::search(Matrix* matrix) {
    stack<State<Point*>*> s;
    s.push(matrix->getInitialState());
    vector<State<Point*>*> nodesEvaluated;
    nodesEvaluated.push_back(matrix->getInitialState());

    while(s.size() != 0) {
        State<Point*>* currentState = s.top();
        s.pop();
        if(matrix->isGoal(currentState)) {
            string s = currentState->backTrace(matrix->getStart());
            int x = 0;
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
                s.push(c);
                nodesEvaluated.push_back(c);
            }
        }
    }
}