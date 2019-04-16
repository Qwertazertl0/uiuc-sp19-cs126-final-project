#include "appState.h"
#include "playGameState.h"
#include "ofMain.h"
#include "ofApp.h"

#include "glm/vec2.hpp"
#include <string>

std::string startMenuBgPath = "graphics/start_menu_background3.jpg";

StartMenuState::StartMenuState() {
  background = new ofImage();
  background->load(startMenuBgPath);
}

void StartMenuState::update() {

}

void StartMenuState::draw() {
  if (background->isAllocated())
    background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void StartMenuState::keyPressed(int key, AppState* currState) {
  currState->setNextState(new PlayGameState());
}

void StartMenuState::keyReleased(int key) {

}

StartMenuState::~StartMenuState() {
  delete background;
}