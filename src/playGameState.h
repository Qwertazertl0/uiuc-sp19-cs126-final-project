#pragma once

#include "ofApp.h"
#include "level.h"
#include <vector>
#include "playGameConstants.h"

class PlayGameState : public AppState {
  ofImage* background;
  ofImage* wrapBackground; //drawn next to background offsreen to simulate wrap

  b2World* world;
  b2Body* dotBody;
  std::list<b2Body*> groundBodies;

  Level demoLevel;

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
  void initGround();
  void initDot();

  void update();
  void draw();
  void drawDot(b2Vec2 pos, float radius);

  void keyPressed(int key);
  void keyReleased(int key);
  bool isInAir();
  std::vector<Clickable*> getClickables();
  void clickOn(Clickable* button);
};