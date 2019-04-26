#include "level.h"

void Level::draw(short absCP) {
  for (auto rect : platforms) {
    rect.draw(absCP);
  }

  for (auto terrain : hills) {
    terrain.draw(absCP);
  }
}