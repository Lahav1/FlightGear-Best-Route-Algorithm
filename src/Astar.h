#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "Matrix.h"
#include "Searcher.h"
#include "AstarPQ.h"

class Astar : public Searcher<Matrix*, string> {
private:
    AstarPQ<State<Point*>*>* open;

public:
    Astar() {};
    string search(Matrix* matrix);
    ~Astar();
};

#endif //MILESTONE2_ASTAR_H
