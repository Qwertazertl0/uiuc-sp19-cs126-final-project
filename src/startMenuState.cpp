#include "startMenuState.h"
#include "playGameState.h"
#include "ofMain.h"
#include "ofApp.h"

#include <string>

std::string startMenuBgPath = "graphics/start_menu_background3.jpg";
std::string testNeutral = "graphics/test.jpg";
std::string testHover = "graphics/test2.jpg";

StartMenuState::StartMenuState() {
  background = new ofImage();
  background->load(startMenuBgPath);

  ofImage* testN = new ofImage(testNeutral);
  ofImage* testH = new ofImage(testHover);
  ofRectangle* testLoc = new ofRectangle(0, 0, 100, 100);
  testButton = new Clickable(testN, testH, testLoc);
}

void StartMenuState::update() {
  
}

void StartMenuState::draw() {
  if (background->isAllocated())
    background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  testButton->draw();
}

void StartMenuState::keyPressed(int key, AppState* currState) {
  currState->setNextState(new PlayGameState());
}

void StartMenuState::keyReleased(int key) {

}

StartMenuState::~StartMenuState() {
  delete background;
}