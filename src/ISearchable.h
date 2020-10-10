#ifndef MILESTONE2_ISEARCHABLE_H
#define MILESTONE2_ISEARCHABLE_H

#include "State.h"
#include <vector>
using namespace std;

template <class T> class ISearchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual bool isGoal(State<T>* s) = 0;
    virtual vector<State<T>*> getPossibleStates(State<T>* s) = 0;
};

#endif //MILESTONE2_ISEARCHABLE_H
