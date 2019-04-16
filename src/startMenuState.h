#pragma once

#include "graphics/ofImage.h"
#include "ofApp.h"

//Assuming window size of 1440x960
//TODO: change to floats for relative positioning
const int menuButtonWidth = 433;
const int menuButtonHeight = 96;
const int startYCoord = 450;
const int optionsYCoord = 560;
const int aboutYCoord = 670;
const int quitYCoord = 780;

const int logoCornerOffset = 82;

class StartMenuState : public AppState {
    ofImage* background;
    ofImage* logo;
  public:
    StartMenuState();
    ~StartMenuState();
    void update();
    void draw();
    void keyPressed(int key, AppState* currState);
    void keyReleased(int key);

    Clickable* startButton;
    Clickable* optionsButton;
    Clickable* aboutButton;
    Clickable* quitButton;
};