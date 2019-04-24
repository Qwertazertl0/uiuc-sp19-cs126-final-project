#pragma once
#include "staticRect.h"

class Level {
public:
  std::vector<StaticRect> platforms;
  void draw(short absCP);
};