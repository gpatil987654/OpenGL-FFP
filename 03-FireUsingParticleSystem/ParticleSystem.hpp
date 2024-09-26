#ifndef _PARTICLE_SYSTEM_H
#define _PARTICLE_SYSTEM_H

#include <vector>
#include "PVector.hpp"
#include "Particle.hpp"

class ParticleSystem
{

private:
    std::vector<Particle> particles;
    PVector emitter;

public:
    ParticleSystem();
    ParticleSystem(PVector l);
    void addParticel();
    PVector random();
    void run();
    bool isEmpty();
};

#endif
