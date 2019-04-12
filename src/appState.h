#pragma once

#include "graphics/ofImage.h"
#include "Box2D/Box2D.h"

class AppState {
  public:
    virtual void update() {}
    virtual void draw() {}
};

class StartMenuState : public AppState {
    ofImage* background;
  public:
    StartMenuState();
    ~StartMenuState();
    void update();
    void draw();
};

class PlayGameState : public AppState {
    BOX2D_H::b2CircleShape* dot;
  public:
    PlayGameState();
    ~PlayGameState();
    void update();
    void draw();
};