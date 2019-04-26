#pragma once

#include "Box2D/Box2D.h"
#include "ofMain.h"
#include "playGameConstants.h"

class StaticPolygon { //Convex polygons only!
  b2Body* body;
  b2Vec2* verts;
  int triangleCount;
  float leftmostPointX;
  float rightmostPointX;
public:
  StaticPolygon(std::vector<float> vertices, b2World* world); //meters

  bool isInView(float absCameraPos); //pixels
  void draw(float absCameraPos); //pixels
};