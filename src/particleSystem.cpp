#include "particleSystem.h"
#include "ofMain.h"
#include <cmath>
#include <random>

ParticleSystem::ParticleSystem(ofImage* image) {
  particleImage = image;
  targetParticleVel.x = 0;
  targetParticleVel.y = 0;
}

ParticleSystem::~ParticleSystem() {
  delete particleImage;
}

void ParticleSystem::init(int numParticles, glm::vec2 initVel) {
  std::srand(std::time(nullptr));
  for (int i = 0; i < numParticles; ++i) {
    int randX = rand() % ofGetWindowWidth();
    int randY = rand() % ofGetWindowHeight();
    createParticle(randX, randY, rand() & updatesPerCycle, getOffsetFactor() * initVel);
  }
  targetParticleNum = numParticles;
  targetParticleVel = initVel;
}

void ParticleSystem::draw() {
  ofPushStyle();
  ofEnableAlphaBlending();
  for (Particle p : particles) {
    ofSetColor(ofColor::white, p.opacity * 255);
    particleImage->draw(p.xCoord, p.yCoord);
  }
  ofDisableAlphaBlending();
  ofPopStyle();
}

void ParticleSystem::updateParticles() {
  auto iter = particles.begin();
  while (iter != particles.end()) {
    iter->life++;
    iter->xCoord += iter->velocity.x;
    iter->yCoord += iter->velocity.y;
    float sinScaleFactor = std::sin(iter->life * M_TWO_PI / updatesPerCycle);
    iter->opacity = defaultOpacity + opacityVariance * sinScaleFactor;
    if (iter->xCoord < -1 * particleImage->getWidth() 
        || iter->yCoord < -1 * particleImage->getHeight()) {
      iter = particles.erase(iter);
    } else {
      ++iter;
    }
  }

  while (particles.size() < targetParticleNum) {
    //Increase probability that particle is generated on the vertical edge
    int randCoord = rand() % glm::max(1, (ofGetWindowWidth() + 3 * ofGetWindowHeight()));
    int xCoord = randCoord;
    int yCoord = ofGetWindowHeight();
    if (randCoord > ofGetWindowWidth()) {
      xCoord = ofGetWindowWidth();
      yCoord -= (randCoord - ofGetWindowWidth()) % ofGetWindowHeight();
    }
    xCoord = redistributeRandomInt(xCoord, ofGetWindowWidth());
    //yCoord = redistributeRandomInt(yCoord, ofGetWindowHeight());
    createParticle(xCoord, yCoord, rand() % updatesPerCycle,
                   getOffsetFactor() * targetParticleVel);
  }
}

void ParticleSystem::createParticle(int x, int y, int life, glm::vec2 vel) {
  Particle p;
  p.xCoord = x;
  p.yCoord = y;
  p.velocity = vel;
  p.life = life;
  particles.push_back(p);
}

void ParticleSystem::clear() {
  particles.clear();
  targetParticleNum = 0;
  targetParticleVel.x = 0;
  targetParticleVel.y = 0;
}

float ParticleSystem::getOffsetFactor() {
  //Gives a factor of 1 +- some percent offset (e.g. 0.8 to 1.2)
  return 1.0f + ((rand() % offsetBound) - offsetBound / 2) / 100.0f;
}

float ParticleSystem::redistributeRandomInt(int val, int max) {
  return std::sqrt(val) * std::sqrt(max);
}