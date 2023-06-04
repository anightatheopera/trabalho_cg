// Purpose: Header file for the Point class.
#ifndef POINT_H
#define POINT_H

class Point {
    public:
        float x;
        float y;
        float z;

        Point();

        Point(float x, float y, float z);

        float getX();
        float getY();
        float getZ();

	    void setX(float x);
	    void setY(float y);
	    void setZ(float z);

        void substract(Point p);
        void normalize();
};

class Point3 {
    public:
        Point p;
        Point n;
        float t[2];

        Point3();
        Point3(Point p, Point n, float t[2]);
        Point3(Point p, Point n);
        Point3(Point p, Point n, Point t);

};

auto cross(Point a, Point b) -> Point;
auto normal(Point a, Point b, Point c) -> Point;

#endif
