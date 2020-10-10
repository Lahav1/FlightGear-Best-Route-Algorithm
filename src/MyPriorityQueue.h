#ifndef MILESTONE2_MYPRIORITYQUEUE_H
#define MILESTONE2_MYPRIORITYQUEUE_H

#include <queue>
#include "State.h"

using namespace std;

template<class T> class MyPriorityQueue {
private:
    vector<T> v;

public:
    /****************************************************
    * Function Name:            push.
    * The Input:                T element.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void push(T element) {
        this->v.push_back(element);
    }

    /****************************************************
    * Function Name:            pop.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void pop() {
        vector<T> temp;
        for(int i = 1; i < v.size(); i++) {
            temp.push_back(v.at(i));
        }
        this->v = temp;
    }

    /****************************************************
    * Function Name:            top.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    T top() {
        return v.at(0);
    }

    /****************************************************
    * Function Name:            remove.
    * The Input:                int index.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void remove(int index) {
        vector<T> temp;
        for(int i = 0; i < v.size(); i++) {
            if(i != index) {
                temp.push_back(v.at(i));
            }
        }
        this->v = temp;
    }

    /****************************************************
    * Function Name:            remove.
    * The Input:                T element.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void remove(T element) {
        vector<T> temp;
        for(int i = 0; i < v.size(); i++) {
            if(v.at(i) != element) {
                temp.push_back(v.at(i));
            }
        }
        this->v = temp;
    }

    /****************************************************
    * Function Name:            size.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    int size() {
        return v.size();
    }

    /****************************************************
    * Function Name:            contain.
    * The Input:                T element.
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool contain(T element) {
        for(auto e : v) {
            if(e == element) {
                return true;
            }
        }
        return false;
    }

    /****************************************************
    * Function Name:            at.
    * The Input:                int index.
    * The Output:
    * The Function Operation:
    ****************************************************/
    T at(int index) {
        return v.at(index);
    }

    /****************************************************
    * Function Name:            update.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void update() {
        for(int i = 0; i < v.size() - 1; i++) {
            for(int j = i; j < v.size() - 1; j++) {
                if(v.at(j)->getCost() > v.at(j + 1)->getCost()) {
                    T temp = v.at(j);
                    v.at(j) = v.at(j + 1);
                    v.at(j + 1) = temp;
                }
            }
        }
    }
};

#endif //MILESTONE2_MYPRIORITYQUEUE_H
