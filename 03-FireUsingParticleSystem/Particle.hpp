#ifndef _PARTCILE_H
#define _PARTCILE_H

#include "PVector.hpp"

class Particle
{
private:
    PVector location;
    PVector velocity;
    PVector acceleration;
    float lifespan;

public:
    static const double size;
    static const double _pi;
    static const double angle[10];
    static const double _cos[10];
    static const double _sin[10];

    Particle();
    Particle(PVector l);
    void run();
    void update();
    void display();
    bool isDead();
    double random(double upper, double lower);
};

#endif
