#ifndef _PVector
#define _PVector

class PVector
{

public:
    double x;
    double y;
    double z;
    PVector();
    PVector(double x1, double y1, double z1);
    void add(const PVector &v);
    PVector operator=(const PVector &other);
};

#endif
