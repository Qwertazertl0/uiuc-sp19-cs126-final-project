#include <iostream>

#include "ofApp.h"
#include "startMenuState.h"

AudioEngine* ofApp::audioEng;
ParticleSystem* ofApp::partSystem;

//--------------------------------------------------------------
void ofApp::setup() {
  ofImage* particleImage = new ofImage();
  particleImage->load(particlePath);
  partSystem = new ParticleSystem(particleImage);
	audioEng = new AudioEngine();

	ofSetEscapeQuitsApp(false);
  gameState = new StartMenuState();
}

void ofApp::exit() {
  delete gameState;
	delete audioEng;
}

//--------------------------------------------------------------
void ofApp::update() {
  gameState->update();
  if (gameState->nextState != gameState) {
    AppState* temp = gameState->nextState;
    delete gameState;
    gameState = temp;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
	gameState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  gameState->keyPressed(key, gameState);
}

void ofApp::keyReleased(int key) {
  gameState->keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button) {
  mousePressInitPosX = x;
  mousePressInitPosY = y;
}

void ofApp::mouseReleased(int x, int y, int button) {
  for (Clickable* button : gameState->getClickables()) {
    if (button->inside(glm::vec2(mousePressInitPosX, mousePressInitPosY))) {
      if (button->inside(glm::vec2(x, y))) {
        gameState->clickOn(button);
        return;
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}