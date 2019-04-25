#pragma once

#include "graphics/ofImage.h"
#include "ofApp.h"
#include "startMenuConstants.h"

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
    ofImage* volumeBar;
    ofImage* jumpLimitText;

    Clickable* startButton;
    Clickable* optionsButton;
    Clickable* aboutButton;
    Clickable* quitButton;
    Clickable* returnButton;
    Clickable* onButton;
    Clickable* offButton;
    Clickable* slider;

    DrawGroup drawItems = MENU;
    bool jumpLimitOn;
    int sliderX = sliderDefaultX;

    bool sliderSelected = false;
    bool mouseOnButton;
    bool isMouseOnButton();
  public:
    StartMenuState(); //Load and instantiate all graphics and Clickables
    StartMenuState(bool jumpLimitOn);
    ~StartMenuState();
    void update();
    void draw();
    void mousePressed();
    std::vector<Clickable*> getClickables();
    void clickOn(Clickable* button);
};