#pragma once

#include "ofApp.h"
#include "level.h"
#include <vector>
#include "playGameConstants.h"
#include "startMenuState.h"

class PlayGameState : public AppState {
  int instructionLifeLimit = 100; //number of update cycles instructions will last
  int instructionLifeCounter = 0;
  int fadeDec = 5;
  ofImage* instructions;

  ofImage* background;
  ofImage* wrapBackground; //drawn next to background offsreen to simulate wrap
  Clickable* homeButton;

  b2World* world;
  b2Body* dotBody;
  std::list<b2Body*> groundBodies;
  Level demoLevel;
  bool jumpLimitOn;
  bool jumped;
  int sliderXPos;

  std::list<b2Vec2> trailPos;
  b2Vec2 prevDotPos;

  short relCameraPos = 0; // value less than screen width
  short absCameraPos = 0;
  short absCameraMax = ofGetWindowWidth() * (numScreenWidths - 1);
public:
  PlayGameState(bool jumpLimit, int sliderX);
  ~PlayGameState();
  void initBox2DWorld();
  void initGameParticles();
  void initStaticBodies();
  void initGround();
  void initDot();
  void drawDot(b2Vec2 pos, float radius);
  void resetDot();

  void update();
  void draw();
  void mousePressed() {};

  void keyPressed(int key);
  void pressA();
  void pressD();
  void pressW();
  void pressSpace();
  bool isInAir();
  std::vector<Clickable*> getClickables();
  void clickOn(Clickable* button);
};