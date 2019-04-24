#include "level.h"

void Level::draw(short absCP) {
  for (auto rect : platforms) {
    rect.draw(absCP);
  }
}