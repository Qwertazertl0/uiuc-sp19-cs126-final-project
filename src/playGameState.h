#pragma once

#include "ofApp.h"
#include <vector>

const float timeStep = 1.0f / 60.0f;
const int velocityIterations = 10;
const int positionIterations = 8;

const b2Vec2 gravity(0.0f, -80.0f);
const float dotRadius = 1.0f;
const float dotDensity = 0.3f;
const float dotFriction = 0.0f;
const float dotHorVelDampFactor = 0.96f;

const int numFadeCircles = 20;
const float fadeStepLen = 0.1f;
const float dotDrawRadius = 40.0f;
const float meterToGraphicsScaleFactor = 40.0f;

const std::string playGameBgPath = "graphics/dark3.jpg";

class PlayGameState : public AppState {
  ofImage* background;
  std::list<b2Vec2> trailPos;

  BOX2D_H::b2World* world;
  BOX2D_H::b2Body* dotBody;
  BOX2D_H::b2Body* groundBody;
  BOX2D_H::b2BodyDef bodyDef;

  b2Vec2 prevDotPos;
public:
  PlayGameState();
  ~PlayGameState();
  void initBox2DWorld();

  void update();
  void draw();
  void drawDot(b2Vec2 pos, float radius);

  void keyPressed(int key, AppState* currState);
  void keyReleased(int key);
  std::vector<Clickable*> getClickables();
  void clickOn(Clickable* button);
};