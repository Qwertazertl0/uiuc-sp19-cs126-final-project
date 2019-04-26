#pragma once
#include "staticRect.h"
#include "staticPolygon.h"

class Level {
public:
  std::vector<StaticRect> platforms;
  std::vector<StaticPolygon> hills;
  void draw(short absCP);
};