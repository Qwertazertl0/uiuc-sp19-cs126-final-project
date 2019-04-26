#include "ofApp.h"
#include "ofMain.h"

Clickable::~Clickable() {
  delete position;
  delete neutralImage;
  if (hoverImage != neutralImage)
    delete hoverImage;
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