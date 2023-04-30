#ifndef POINT_H
#define POINT_H

class Point {
    public:
        double x;
        double y;
        double z;

        Point();

        Point(double x, double y, double z);

        double getX();
        double getY();
        double getZ();

	    void setX(double x);
	    void setY(double y);
	    void setZ(double z);

        void substract(Point p);
};

#endif
