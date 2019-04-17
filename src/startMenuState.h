#pragma once

#include "graphics/ofImage.h"
#include "ofApp.h"

//Positioning of buttons in pixels
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
    StartMenuState(); //Load and instantiate all graphics and Clickables
    ~StartMenuState();
    void update();
    void draw();
    std::vector<Clickable*> getClickables();
    void clickOn(Clickable* button);

    Clickable* startButton;
    Clickable* optionsButton;
    Clickable* aboutButton;
    Clickable* quitButton;
};