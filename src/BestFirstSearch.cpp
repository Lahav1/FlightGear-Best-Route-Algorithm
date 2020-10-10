#include "BestFirstSearch.h"

/****************************************************
* Function Name:            constructor.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
BestFirstSearch::BestFirstSearch() {}

/****************************************************
* Function Name:            search.
* The Input:                Matrix* matrix.
* The Output:
* The Function Operation:
****************************************************/
string BestFirstSearch::search(Matrix* matrix) {
    this->open = new MyPriorityQueue<State<Point*>*>;
    State<Point*>* start = matrix->getInitialState();
    start->setCameFrom(nullptr);
    start->setCost(((MatrixNode*) start)->getValue());
    this->open->push(start);
    vector<State<Point*>*> close;
    while(this->open->size() != 0) {
        this->open->update();
        State<Point*>* n = this->open->top();
        this->open->pop();
        close.push_back(n);
        if(matrix->isGoal(n)) {
            start->setCameFrom(nullptr);
            string y = n->backTrace(matrix->getStart());
            int x = 0;
            return y;
        }
        vector<State<Point*>*> possibleStates = matrix->getPossibleStates(n);
        for(auto s : possibleStates) {
            bool openContains = this->open->contain(s);
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
                this->open->push(s);
                this->open->update();
            } else {
                State<Point*>* tmp = nullptr;
                for(int i = 0; i < this->open->size(); i++) {
                    if(s->equals(this->open->at(i)) && (s->getCost() < this->open->at(i)->getCost())) {
                        if(!openContains) {
                            s->setCost(((MatrixNode*) s)->getValue() + n->getCost() + 1);
                            s->setCameFrom(n);
                            this->open->push(s);
                            this->open->update();
                        } else {
                            tmp = this->open->at(i);
                            this->open->remove(tmp);
                            s->setCost(((MatrixNode*) s)->getValue() + n->getCost() + 1);
                            s->setCameFrom(n);
                            this->open->push(s);
                            this->open->update();
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
BestFirstSearch::~BestFirstSearch() {
    delete(this->open);
}