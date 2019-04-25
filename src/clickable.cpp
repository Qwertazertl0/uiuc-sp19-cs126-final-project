#include "ofApp.h"
#include "ofMain.h"

Clickable::~Clickable() {
  delete neutralImage;
  delete hoverImage;
  delete position;
}

void Clickable::draw() {
  if (position->inside(glm::vec2(ofGetMouseX(), ofGetMouseY()))) {
    hoverImage->draw(*position);
  } else {
    neutralImage->draw(*position);
  }
}

bool Clickable::inside(glm::vec2 mousePos) {
  return position->inside(mousePos);
}