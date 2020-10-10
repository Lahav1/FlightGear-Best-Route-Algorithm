#ifndef MILESTONE2_ISEARCHER_H
#define MILESTONE2_ISEARCHER_H

#include "ISearchable.h"
#include "Point.h"
#include "MyPriorityQueue.h"

template<class P, class S> class ISearcher {
protected:

public:
    virtual S search(P searchable) = 0;
};

#endif //MILESTONE2_ISEARCHER_H
