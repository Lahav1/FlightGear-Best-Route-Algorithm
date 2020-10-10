#include "Point.h"

/****************************************************
* Function Name:            Point.
* The Input:                int xp, int yp.
* The Output:
* The Function Operation:
****************************************************/
Point::Point(int xp, int yp) {
    this->x = xp;
    this->y = yp;
}

/****************************************************
* Function Name:            getX.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
int Point::getX() {
    return this->x;
}

/****************************************************
* Function Name:            getY.
* The Input:
* The Output:
* The Function Operation:
****************************************************/
int Point::getY() {
    return this->y;
}

/****************************************************
* Function Name:            calculateDistance.
* The Input:                Point *p.
* The Output:
* The Function Operation:
****************************************************/
double Point::calculateDistance(Point *p) {
    int x1 = this->x;
    int x2 = p->getX();
    int y1 = this->y;
    int y2 = p->getY();
    double distance = sqrt(pow((y1 - y2), 2) + pow((x1 - x2), 2));
    return distance;
}

/****************************************************
* Function Name:            overloads operator==.
* The Input:                Point other.
* The Output:
* The Function Operation:
****************************************************/
bool Point::operator==(Point other) {
    return ((this->x == other.getX()) && (this->y == other.getY()));
}