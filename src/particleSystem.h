#pragma once

#include "ofMain.h"

const int updatesPerCycle = 150; //controls opacity periodicity
const float opacityVariance = 0.20f;
const float defaultOpacity = 0.5f;
const int offsetBound = 100; //offset for velocity variance
                            //  e.g. an offsetBound of 20 is targetVel +/- 10%

//Represents one particle object emitted by particle emitter
struct Particle {
  int life = 0; // in updates
  float xCoord = 0; // in pixels
  float yCoord = 0; // in pixels
  float opacity = defaultOpacity;

  glm::vec2 velocity; // in pixels/update 
};

//Handles creation, update, and rendering of particles
class ParticleSystem {
    ofImage* particleImage;
    std::list<Particle> particles;
    glm::vec2 targetParticleVel;

    int targetParticleNum = 0;
  public:
    ParticleSystem(ofImage* image);
    ~ParticleSystem();
    void init(int numParticles, glm::vec2 initVel); //randomly scatters particles throughout screen
    void draw();
    void updateParticles();
    void createParticle(int x, int y, int life, glm::vec2 vel);
    void clear(); //clears particles and target values

    float getOffsetFactor();
    //curves range of random ints so higher values are more probable
    float redistributeRandomInt(int val, int max); 
};
