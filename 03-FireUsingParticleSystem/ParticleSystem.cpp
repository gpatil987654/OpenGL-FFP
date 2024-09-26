#include "ParticleSystem.hpp"

#include <iostream>
#include <cmath>
#include <stdlib.h>

ParticleSystem::ParticleSystem(PVector l)
{
    emitter = l;
}

void ParticleSystem::addParticel()
{
    PVector tmp = random();
    tmp.add(emitter);
    Particle p(tmp);
    particles.push_back(p);
}

void ParticleSystem::run()
{
    std::vector<Particle>::iterator it;

    for (it = particles.begin(); it < particles.end();)
    {
        if (!(*it).isDead())
        {
            (*it).run();
            it++;
        }
        else
        {
            it = particles.erase(it);
        }
    }
}

PVector ParticleSystem::random()
{
    double lower = -0.04f;
    double upper = 0.04;
    double range = upper - lower;
    double rand_x = lower + (range * ((double)rand()) / (RAND_MAX));
    double rand_y = lower + (range * ((double)rand()) / (RAND_MAX));

    return PVector(rand_x, rand_y, 0);
}
bool ParticleSystem::isEmpty()
{
    if (particles.size() == 0)
        return true;
    else
        return false;
}
