#ifndef MILESTONE2_POINT_H
#define MILESTONE2_POINT_H

#include <math.h>

class Point {
private:
    int x;
    int y;

public:
    Point(int xp, int yp);
    int getX();
    int getY();
    double calculateDistance(Point* p);
    bool operator==(Point other);
};

#endif //MILESTONE2_POINT_H
