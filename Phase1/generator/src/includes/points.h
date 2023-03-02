#ifndef POINT_H
#define POINT_H

class Point {
    private:
        double x;
        double y;
        double z;

    public:
        Point();

        Point(double x, double y, double z);

        double getX();
        double getY();
        double getZ();

	void setX(double x);
	void setY(double y);
	void setZ(double z);

};

#endif
