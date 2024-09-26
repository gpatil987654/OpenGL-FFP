#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <cmath>
#include "Particle.hpp"

float lerp(float start, float end, float t);

const double Particle::size = 0.04f;
const double Particle::_pi = 3.141592;
const double Particle::angle[10] = {2 * _pi * 1 / 10.0, 2 * _pi * 2 / 10.0, 2 * _pi * 3 / 10.0, 2 * _pi * 4 / 10.0, 2 * _pi * 5 / 10.0, 2 * _pi * 6 / 10.0, 2 * _pi * 7 / 10.0, 2 * _pi * 8 / 10.0, 2 * _pi * 9 / 10.0, 2 * _pi};
const double Particle::_cos[10] = {size * cos(angle[0]), size *cos(angle[1]), size *cos(angle[2]), size *cos(angle[3]), size *cos(angle[4]), size *cos(angle[5]), size *cos(angle[6]), size *cos(angle[7]), size *cos(angle[8]), size *cos(angle[9])};
const double Particle::_sin[10] = {size * sin(angle[0]), size *sin(angle[1]), size *sin(angle[2]), size *sin(angle[3]), size *sin(angle[4]), size *sin(angle[5]), size *sin(angle[6]), size *sin(angle[7]), size *sin(angle[8]), size *sin(angle[9])};

Particle ::Particle()
{
}

Particle::Particle(PVector l)
{
    location = l;
    velocity = PVector(0.0f, 0.001, 0);
    lifespan = 255;
}

void Particle::run()
{
    update();
    display();
}

double Particle::random(double upper, double lower)
{
    double range = (upper - lower);
    double random_double = lower + (range * ((double)rand()) / (RAND_MAX));
    return random_double;
}

void Particle::update()
{
    double x_acc = 0.000034 * random(-1, 1);
    double y_acc = 0.00001 * random(-1, 1);
    double z_acc = 0.0f;

    acceleration = PVector(x_acc, y_acc, z_acc);
    velocity.add(acceleration);
    location.add(velocity);
    lifespan -= 0.2;
}

void Particle::display()
{
    double inty = 1.2 - lifespan / 255.0;

    if (lifespan < 50)
        glColor4f(0.9f, 0.9f, 0.9f, inty);
    else
        glColor4f(1.0f, lerp(1.0f, 0.0f, (200.0f - lifespan) / 200.0f), 0.0f, inty);

    glBegin(GL_POLYGON);
    for (std::size_t i = 0; i < 10; i++)
    {
        glVertex3f(location.x + _cos[i], location.y + _sin[i], 0);
    }
    glEnd();
}

bool Particle::isDead()
{
    if (lifespan < 0.0f)
        return true;
    else
        return false;
}
