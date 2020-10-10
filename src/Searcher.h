#ifndef MILESTONE2_SEARCHER_H
#define MILESTONE2_SEARCHER_H

#include "ISearcher.h"

template<class P, class S> class Searcher : public ISearcher<P, S> {
public:
    virtual S search(P s) = 0;
};

#endif //MILESTONE2_SEARCHER_H
