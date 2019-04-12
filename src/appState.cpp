#include "appState.h"
#include "ofMain.h"

#include <string>

std::string startMenuBgPath = "graphics/start_menu_background.jpg";

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

StartMenuState::~StartMenuState() {
  delete background;
}

//-----------------------------------------------------------------------------
PlayGameState::PlayGameState() {

}

void PlayGameState::update() {

}

void PlayGameState::draw() {

}

PlayGameState::~PlayGameState() {

}