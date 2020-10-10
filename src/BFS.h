#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "Matrix.h"
#include "Searcher.h"
#include <queue>

using namespace std;

class BFS : public Searcher<Matrix*, string> {

public:
    BFS();
    string search(Matrix* matrix);
};
#endif //MILESTONE2_BFS_H
