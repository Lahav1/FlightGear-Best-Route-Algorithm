#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

#include "string"

using namespace std;

template <class T> class State {
protected:
    T state;
    double cost;                        //g
    double heuristicValueFromGoal;      //h
    double f;                           //f = h + g (heuristic + cost)
    State<T>* cameFrom;

public:
    /****************************************************
    * Function Name:            constructor.
    * The Input:
    * The Output:
    * The Function Operation:   default constructor.
    ****************************************************/
    State<T>(){}

    /****************************************************
    * Function Name:            constructor.
    * The Input:                T s : state's type.
    * The Output:
    * The Function Operation:
    ****************************************************/
    State<T>(T s) {
        this->state = s;
        this->cost = 0;
        this->cameFrom = nullptr;
    }

    /****************************************************
    * Function Name:            setCost.
    * The Input:                double c : cost of the state.
    * The Output:
    * The Function Operation:   sets the cost of the state.
    ****************************************************/
    void setCost(double c) {
        this->cost = c;
    }

    /****************************************************
    * Function Name:            setCameFrom.
    * The Input:                State<T>* cf : a pointer to another state.
    * The Output:
    * The Function Operation:   connects current state with the state which came before him.
    ****************************************************/
    void setCameFrom(State<T>* cf) {
        this->cameFrom = cf;
    }

    /****************************************************
    * Function Name:            getState.
    * The Input:
    * The Output:               T state.
    * The Function Operation:   returns the value of the type the state is based on.
    ****************************************************/
    T getState() {
        return this->state;
    }

    /****************************************************
    * Function Name:            equals.
    * The Input:                State<T>* s : another state.
    * The Output:               true/false.
    * The Function Operation:   returns true if states are equal. the states are compared by their state member,
     *                          which is the Point* when talking about matrix.
    ****************************************************/
    bool equals(State<T>* s) {
        return this->state == s->getState();
    }

    /****************************************************
    * Function Name:            backTrace.
    * The Input:                Point* start : a pointer to the matrix's start point.
    * The Output:
    * The Function Operation:   recursively build the backtrace from start point to current point.
    ****************************************************/
    string backTrace(T start) {
        if (*(this->getState()) == *start) {
            return "";
        }
        string path = cameFrom->backTrace(start);
        if(cameFrom->getState()->getX() < this->getState()->getX()) {
            path += "Right,";
        }
        else if(cameFrom->getState()->getX() > this->getState()->getX()) {
            path += "Left,";
        }
        else if(cameFrom->getState()->getY() < this->getState()->getY()) {
            path += "Down,";
        }
        else if(cameFrom->getState()->getY() > this->getState()->getY()) {
            path += "Up,";
        }
        return path;
    }

    /****************************************************
    * Function Name:            getCost.
    * The Input:
    * The Output:               double cost.
    * The Function Operation:   getter to state's cost.
    ****************************************************/
    double getCost() {
        return this->cost;
    }

    /****************************************************
    * Function Name:            overrides > operator.
    * The Input:                State<T> &other.
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator>(State<T> &other) {
        return (this->getCost() > other->getCost());
    }

    /****************************************************
    * Function Name:            overrides < operator.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator<(State<T> &other) {
        return (this->getCost() < other->getCost());
    }

    /****************************************************
    * Function Name:            overrides >= operator.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator>=(State<T> &other) {
        return (this->getCost() >= other->getCost());
    }

    /****************************************************
    * Function Name:            overrides <= operator.
    * The Input:                State<T> &other.
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator<=(State<T> &other) {
        return (this->getCost() <= other->getCost());
    }

    /****************************************************
    * Function Name:            overrides == operator.
    * The Input:                State<T> &other.
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator==(State<T> &other) {
        return (this->getState() == other->getState());
    }

    /****************************************************
    * Function Name:            overrides != operator.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    bool operator!=(State<T> &other) {
        return (this->getState() != other->getState());
    }

    /****************************************************
    * Function Name:            setHeuristicValue.
    * The Input:                double v.
    * The Output:
    * The Function Operation:
    ****************************************************/
    void setHeuristicValue(double v) {
        this->heuristicValueFromGoal = v;
        f = cost + heuristicValueFromGoal;
    }

    /****************************************************
    * Function Name:            getHeuristicValue.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    double getHeuristicValue() {
        return this->heuristicValueFromGoal;
    }

    /****************************************************
    * Function Name:            setF.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    void setF(double v) {
        this->f = v;
    }

    /****************************************************
    * Function Name:            getF.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    double getF() {
        return this->f;
    }
};

#endif //MILESTONE2_STATE_H
