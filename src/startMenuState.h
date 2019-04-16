#pragma once

#include "graphics/ofImage.h"
#include "ofApp.h"

class StartMenuState : public AppState {
    ofImage* background;
  public:
    StartMenuState();
    ~StartMenuState();
    void update();
    void draw();
    void keyPressed(int key, AppState* currState);
    void keyReleased(int key);

    Clickable* testButton;
};