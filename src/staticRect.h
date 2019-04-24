#pragma once

#include "Box2D/Box2D.h"
#include "ofMain.h"
#include "playGameConstants.h"

class StaticRect {
  b2Body* body;
  int hw, hh; //half-width, half-height in meters
public:
  StaticRect(int w, int h, float x, float y, b2World* world); //meters

  bool isInView(float absCameraPos); //pixels
  void draw(float absCameraPos); //pixels
};