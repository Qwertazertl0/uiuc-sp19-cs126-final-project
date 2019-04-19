#include "particleSystem.h"
#include "ofMain.h"

ParticleSystem::ParticleSystem(ofImage* image) {
  particleImage = image;
}

ParticleSystem::~ParticleSystem() {
  delete particleImage;
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
    iter->xCoord += iter->velocity.x;
    iter->yCoord += iter->velocity.y;
    if (iter->xCoord < -100 || iter->yCoord < -100) {
      iter = particles.erase(iter);
    } else {
      ++iter;
    }
  }
}

void ParticleSystem::createParticle() {
  Particle p;
  p.xCoord = ofGetWindowWidth();
  p.yCoord = ofGetWindowHeight();
  p.velocity = glm::vec2(-5, -3);
  particles.push_back(p);
}