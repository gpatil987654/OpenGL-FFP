#include "PVector.hpp"

PVector::PVector()
{
    x = 0;
    y = 0;
    z = 0;
};

PVector::PVector(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
};

void PVector::add(const PVector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
};

PVector PVector::operator=(const PVector &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
};

