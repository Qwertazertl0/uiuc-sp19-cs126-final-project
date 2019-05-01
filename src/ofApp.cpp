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
  ofSetFrameRate(30);
}

void ofApp::exit() {
  delete gameState;
	delete audioEng;
}

//--------------------------------------------------------------
void ofApp::update() {
  if (ofGetWindowWidth() == 0) return; //Avoids numerical issues upon window minimization
  gameState->update();
  if (gameState->nextState != gameState) {
    AppState* temp = gameState->nextState;
    delete gameState;
    if (temp == nullptr) {
      ofExit(0);
    }
    gameState = temp;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (ofGetWindowWidth() == 0) return;
  ofPushStyle();
  ofSetColor(ofColor::black);
  ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  ofPopStyle();
	if (gameState) 
    gameState->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  gameState->keyPressed(key);
}

void ofApp::keyReleased(int key) {
  gameState->keyReleased(key);
}

void ofApp::mousePressed(int x, int y, int button) {
  mousePressInitPosX = x;
  mousePressInitPosY = y;
  gameState->mousePressed();
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