#include "staticRect.h"
#include "ofApp.h"

StaticRect::StaticRect(float w, float h, float x, float y, b2World *world) {
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
  float absCamPos_m = absCamPos / pixelsPerMeter;
  bool pastLeftEdge = absCamPos_m < (body->GetPosition().x + hw);
  bool beforeRightEdge = body->GetPosition().x < (screenWidthMeters + absCamPos_m + 2*hw);
  return pastLeftEdge && beforeRightEdge;
}

void StaticRect::draw(float absCamPos) {
  if (isInView(absCamPos)) {
    int centerPos_x = body->GetPosition().x * pixelsPerMeter - absCamPos;
    int centerPos_y = ofGetWindowHeight() - body->GetPosition().y * pixelsPerMeter - groundOffset;
    int ofCoord_x = centerPos_x - hw * pixelsPerMeter;
    int ofCoord_y = centerPos_y - hh * pixelsPerMeter;
    ofPushStyle();
      ofSetColor(ofColor::darkGray);
      ofDrawRectangle(ofCoord_x, ofCoord_y, 2*hw*pixelsPerMeter, 2*hh*pixelsPerMeter);
    ofPopStyle();
  }
}