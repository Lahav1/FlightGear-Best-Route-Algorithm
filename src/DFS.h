#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "Matrix.h"
#include "Searcher.h"
#include <stack>

class DFS : public Searcher<Matrix*, string>{
public:
    DFS();
    string search(Matrix* matrix);
};

#endif //MILESTONE2_DFS_H
