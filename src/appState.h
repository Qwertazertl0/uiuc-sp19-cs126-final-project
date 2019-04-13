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

class PlayGameState : public AppState {
    ofImage* background;
    ofFbo* fadeBuffer;
    
    BOX2D_H::b2World* world;
    BOX2D_H::b2Body* dotBody;
    BOX2D_H::b2Body* groundBody;
    BOX2D_H::b2BodyDef bodyDef;
  public:
    PlayGameState();
    ~PlayGameState();
    void initBox2DWorld();
    void update();
    void draw();
    void keyPressed(int key, AppState* currState);
    void keyReleased(int key);

    bool wKeyPressed = false;
};