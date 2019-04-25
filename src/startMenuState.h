#pragma once

#include "graphics/ofImage.h"
#include "ofApp.h"

//Positioning of buttons/labels in pixels (assumes screen is 1440x960)
const int menuButtonWidth = 433;
const int menuButtonHeight = 96;
const int startYCoord = 450;
const int optionsYCoord = 560;
const int aboutYCoord = 670;
const int quitYCoord = 780;
const int logoCornerOffset = 82;
const int returnWidth = 292;
const int returnHeight = 141;
const int returnXCoord = 574;
const int returnYCoord = 735;
const int aboutTextX = 108;
const int aboutTextY = 126;
const int volTextX = 191;
const int volTextY = 234;
const int jumpLimX = 183;
const int jumpLimY = 488;
const int onOffX = 652;
const int onOffY = 473;
const int onOffWidth = 181;
const int onOffHeight = 110;

//Particles constants
const int numInitParticles = 80;
const glm::vec2 initVel(-0.7, -0.14);

//Sets of items to draw
enum DrawGroup {
  MENU = 0,
  OPTIONS,
  ABOUT
};

class StartMenuState : public AppState {
    ofImage* background;
    ofImage* logo;
    ofImage* aboutText;
    ofImage* volumeText;
    ofImage* jumpLimitText;

    Clickable* startButton;
    Clickable* optionsButton;
    Clickable* aboutButton;
    Clickable* quitButton;
    Clickable* returnButton;
    Clickable* onButton;
    Clickable* offButton;

    DrawGroup drawItems = MENU;
    bool jumpLimitOn = true;

    bool mouseOnButton;
    bool isMouseOnButton();
  public:
    StartMenuState(); //Load and instantiate all graphics and Clickables
    ~StartMenuState();
    void update();
    void draw();
    std::vector<Clickable*> getClickables();
    void clickOn(Clickable* button);
};