#include "Astar.h"

/****************************************************
* Function Name:            search.
* The Input:                Matrix* matrix.
* The Output:               string path.
* The Function Operation:   prints the solution
****************************************************/
string Astar::search(Matrix* matrix) {
    int nodesEvaluated = 0;
    this->open = new AstarPQ<State<Point*>*>;
    State<Point*>* start = matrix->getInitialState();
    start->setCameFrom(nullptr);
    start->setCost(((MatrixNode*) start)->getValue());
    // pushing the start node with updated values.
    open->push(start);
    vector<State<Point*>*> close;
    while(open->size() != 0) {
        open->update();
        State<Point*>* n = open->top();
        open->pop();
        nodesEvaluated++;
        close.push_back(n);
        //if the cureent state is our goal we finish the algorithm and return the backtrace.
        if(matrix->isGoal(n)) {
            start->setCameFrom(nullptr);
            string y = n->backTrace(matrix->getStart());
            return y;
        }
        vector<State<Point*>*> possibleStates = matrix->getPossibleStates(n);
        //Going over all the possible states from current state.
        for(auto s : possibleStates) {
            bool openContains = open->contain(s);
            bool closeContains = false;
            for(auto node : close) {
                if(s == node) {
                    closeContains = true;
                    break;
                }
            }
            if(!openContains && !closeContains) {
                s->setCameFrom(n);
                s->setCost(((MatrixNode*) s)->getValue() + n->getCost() + 1);
                open->push(s);
                open->update();
            } else {
                State<Point*>* tmp = nullptr;
                for(int i = 0; i < open->size(); i++) {
                    if(s->equals(open->at(i)) && (s->getCost() < open->at(i)->getCost())) {
                        if(!openContains) {
                            s->setCost(((MatrixNode*) s)->getValue() + n->getCost() + 1);
                            s->setCameFrom(n);
                            open->push(s);
                            open->update();
                        } else {
                            tmp = open->at(i);
                            open->remove(tmp);
                            s->setCost(((MatrixNode*) s)->getValue() + n->getCost() + 1);
                            s->setCameFrom(n);
                            open->push(s);
                            open->update();
                            break;
                        }
                    }
                }
            }
        }
    }
}

/****************************************************
* Function Name:            destructor.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
Astar::~Astar() {
    delete(this->open);
}