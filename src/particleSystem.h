#pragma once

#include "ofMain.h"

//Represents one particle object emitted by particle emitter
struct Particle {
  int xCoord = 0;
  int yCoord = 0;
  float opacity = 0.5f;

  glm::vec2 velocity; // in pixels/update 
};

//Handles creation, update, and rendering of particles
class ParticleSystem {
    ofImage* particleImage;
    std::list<Particle> particles;
  public:
    ParticleSystem(ofImage* image);
    ~ParticleSystem();
    void draw();
    void updateParticles();
    void createParticle();
};
