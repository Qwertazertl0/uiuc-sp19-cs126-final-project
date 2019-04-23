#pragma once

#include "ofApp.h"
#include <vector>

//Box2D world physics solver parameters
const float timeStep = 1.0f / 60.0f;
const int velocityIterations = 10;
const int positionIterations = 8;

//World and Dot physical constants
const b2Vec2 gravity(0.0f, -80.0f);
const float dotRadius = 1.0f;
const float dotDensity = 0.3f;
const float dotFriction = 0.0f;
const float dotHorVelDampFactor = 0.96f;

//Dot graphics constants
const int numFadeCircles = 15;
const float dotDrawRadius = 40.0f;
const float fadeRadiusShrinkage = 20.0f;

//Static body constants
const int groundOffset = 20;

//Camera constants
const int cameraPanDist = 400; // in pixels
const int numScreenWidths = 3;

//Miscellaneous
const float meterInPixels = 40.0f;
const std::string playGameBgPath = "graphics/gameBackground3.jpg";

class PlayGameState : public AppState {
  ofImage* background;
  ofImage* wrapBackground; //drawn next to background offsreen to simulate wrap

  BOX2D_H::b2World* world;
  BOX2D_H::b2Body* dotBody;
  BOX2D_H::b2BodyDef bodyDef;

  std::list<b2Vec2> trailPos;
  b2Vec2 prevDotPos;

  short relCameraPos = 0; // value less than screen width
  short absCameraPos = 0;
  short absCameraMax = ofGetWindowWidth() * (numScreenWidths - 1);
public:
  PlayGameState();
  ~PlayGameState();
  void initBox2DWorld();
  void initStaticBodies();
  void initDot();

  void update();
  void draw();
  void drawDot(b2Vec2 pos, float radius);

  void keyPressed(int key, AppState* currState);
  void keyReleased(int key);
  std::vector<Clickable*> getClickables();
  void clickOn(Clickable* button);
};