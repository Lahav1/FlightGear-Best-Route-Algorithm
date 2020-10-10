#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H

#include "Matrix.h"
#include "Searcher.h"
#include "MyPriorityQueue.h"

class BestFirstSearch : public Searcher<Matrix*, string> {
private:
    MyPriorityQueue<State<Point*>*>* open;

public:
    BestFirstSearch();
    string search(Matrix* matrix);
    ~BestFirstSearch();
};

#endif //MILESTONE2_BESTFIRSTSEARCH_H
