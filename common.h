#ifndef COMMON_H
#define COMMON_H

struct point
{
    point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    double x;
    double y;
};

struct point3d
{
    point3d(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double x;
    double y;
    double z;
};
#endif
