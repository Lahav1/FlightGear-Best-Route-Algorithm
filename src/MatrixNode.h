#ifndef MILESTONE2_MATRIXNODE_H
#define MILESTONE2_MATRIXNODE_H

#include "Point.h"
#include "State.h"

class MatrixNode : public State<Point*> {
private:
    int value;

public:
    /****************************************************
    * Function Name:            constructor.
    * The Input:                Point* p, int val.
    * The Output:
    * The Function Operation:
    ****************************************************/
    MatrixNode(Point* p, int val) {
        this->state = p;
        this->value = val;
        this->cost = 0;
        this->cameFrom = nullptr;
    }

    /****************************************************
    * Function Name:            getCoordinates.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    Point* getCoordinates() {
        return this->state;
    }

    /****************************************************
    * Function Name:            getValue.
    * The Input:
    * The Output:
    * The Function Operation:
    ****************************************************/
    int getValue() {
        return this->value;
    }

    /****************************************************
    * Function Name:            calculateAerialDistance.
    * The Input:                MatrixNode* n.
    * The Output:
    * The Function Operation:
    ****************************************************/
    double calculateAerialDistance(MatrixNode* n) {
        Point* p1 = this->state;
        Point* p2 = n->getCoordinates();
        return p1->calculateDistance(p2);
    }

    /****************************************************
    * Function Name:            destructor.
    * The Input:
    * The Output:
    * The Function Operation:   removes the point.
    ****************************************************/
    ~MatrixNode() {
        delete(this->state);
    }

    /****************************************************
    * Function Name:            calculateManhattanDistance.
    * The Input:                MatrixNode* n.
    * The Output:               double manhattan distance.
    * The Function Operation:
    ****************************************************/
    double calculateManhattanDistance(MatrixNode* n) {
        Point* p1 = this->state;
        Point* p2 = n->getCoordinates();
        int result = abs(p2->getX() - p1->getX()) + abs(p2->getY() - p1->getY());
        return result;
    }
};

#endif //MILESTONE2_MATRIXNODE_H
