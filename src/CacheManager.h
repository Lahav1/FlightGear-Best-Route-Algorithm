#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

#include "Lexer.h"
#include <unordered_map>

using namespace std;

template <class P, class S> class CacheManager {
public:
    virtual void loadFromFile() = 0;
    virtual void addNewSolution(P problem, S solution) = 0;
    virtual S findSolution(P problem) = 0;
    virtual pair<string, string> getSolverTypes() = 0;
    virtual bool isSaved(P problem) = 0;
};

#endif //MILESTONE2_CACHEMANAGER_H
