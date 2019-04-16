#pragma once

#include "graphics/ofImage.h"
#include "Box2D/Box2D.h"

class AppState {
  public:
    virtual void update() {}
    virtual void draw() {}
    virtual void keyPressed(int key, AppState* currState) {}
    virtual void keyReleased(int key) {}
    void setNextState(AppState* state) {
      nextState = state;
    }

    AppState* nextState = this;
};

class StartMenuState : public AppState {
    ofImage* background;
  public:
    StartMenuState();
    ~StartMenuState();
    void update();
    void draw();
    void keyPressed(int key, AppState* currState);
    void keyReleased(int key);
};