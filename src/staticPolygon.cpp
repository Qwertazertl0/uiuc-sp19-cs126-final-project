#include "staticPolygon.h"

StaticPolygon::StaticPolygon(std::vector<float> vertices, b2World* world) {
  b2BodyDef bodyDef;
  bodyDef.position.Set(0, 0);
  body = world->CreateBody(&bodyDef);

  vert = new b2Vec2[vertices.size() / 2];
  float minPos;
  float maxPos;
  for (int i = 0; i < vertices.size(); i += 2) {
    float x = vertices.at(i);
    if (i == 0) {
      minPos = x;
      maxPos = x;
    } else {
      if (x < minPos) {
        minPos = x;
      } else if (x > maxPos) {
        maxPos = x;
      }
    }
    vert[i / 2].Set(vertices.at(i), vertices.at(i + 1));
  }
  leftmostPointX = minPos;
  rightmostPointX = maxPos;
  triangleCount = vertices.size() / 2 - 2;

  b2PolygonShape polygon;
  polygon.Set(vert, vertices.size() / 2);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &polygon;
  body->CreateFixture(&fixtureDef);
}

bool StaticPolygon::isInView(float absCamPos) {
  float absCamPos_m = absCamPos / pixelsPerMeter;
  bool pastLeftEdge = rightmostPointX > absCamPos_m;
  bool beforeRightEdge = leftmostPointX < (absCamPos_m + screenWidthMeters);
  return pastLeftEdge && beforeRightEdge;
}

void StaticPolygon::draw(float absCamPos) {
  if (isInView(absCamPos)) {
    b2Vec2 anchor = vert[0];
    float v0_x = anchor.x * pixelsPerMeter - absCamPos;
    float v0_y = ofGetWindowHeight() - anchor.y * pixelsPerMeter - groundOffset;

    b2Vec2 v1, v2;
    int vertIndex = 1;
    for (int i = 0; i < triangleCount; ++i) {
      v1.Set(vert[vertIndex].x, vert[vertIndex].y);
      ++vertIndex;
      v2.Set(vert[vertIndex].x, vert[vertIndex].y);
      float v1_x = v1.x * pixelsPerMeter - absCamPos;
      float v2_x = v2.x * pixelsPerMeter - absCamPos;
      float v1_y = ofGetWindowHeight() - v1.y * pixelsPerMeter - groundOffset;
      float v2_y = ofGetWindowHeight() - v2.y * pixelsPerMeter - groundOffset;
      ofPushStyle();
        ofSetColor(ofColor::darkGray);
        ofDrawTriangle(v0_x, v0_y, v1_x, v1_y, v2_x, v2_y);
      ofPopStyle();
    }
  }
}