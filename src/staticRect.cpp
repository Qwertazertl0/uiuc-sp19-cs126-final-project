#include "staticRect.h"
#include "ofApp.h"

StaticRect::StaticRect(int w, int h, float x, float y, b2World *world) {
  b2BodyDef bodyDef;
  bodyDef.position.Set(x, y);
  body = world->CreateBody(&bodyDef);

  hw = w / 2;
  hh = h / 2;
  b2PolygonShape rect;
  rect.SetAsBox(hw, hh);
  
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &rect;
  body->CreateFixture(&fixtureDef);
}

bool StaticRect::isInView(float absCamPos) {
  float absCamPos_m = absCamPos / meterInPixels;
  bool pastLeftEdge = absCamPos_m < (body->GetPosition().x + hw);
  bool beforeRightEdge = body->GetPosition().x < (screenWidthMeters + absCamPos_m - hw);
  return pastLeftEdge && beforeRightEdge;
}

void StaticRect::draw(float absCamPos) {
  if (isInView(absCamPos)) {
    int centerPos_x = body->GetPosition().x * meterInPixels - absCamPos;
    int centerPos_y = ofGetWindowHeight() - body->GetPosition().y * meterInPixels - groundOffset;
    int ofCoord_x = centerPos_x - hw * meterInPixels;
    int ofCoord_y = centerPos_y - hh * meterInPixels;
    ofPushStyle();
      ofSetColor(ofColor::white);
      ofDrawRectangle(ofCoord_x, ofCoord_y, 2*hw*meterInPixels, 2*hh*meterInPixels);
    ofPopStyle();
  }
}