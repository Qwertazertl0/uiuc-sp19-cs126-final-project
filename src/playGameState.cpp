#include "playGameState.h"
#include "ofMain.h"
#include "Box2D\Box2D.h"
#include <algorithm>

PlayGameState::PlayGameState() {
  background = new ofImage();
  background->load(playGameBgPath);
  wrapBackground = new ofImage();
  wrapBackground->load(playGameBgPath);

  initBox2DWorld();
}

void PlayGameState::initBox2DWorld() {
  world = new b2World(gravity);
  initStaticBodies();
  initDot();
}

void PlayGameState::initStaticBodies() {
  b2BodyDef bodyDef;

  StaticRect p(8, 4, 30, 2, world);
  demoLevel.platforms.push_back(p);

  //non-ground bounding edges
  b2Body* worldEdge;
  worldEdge = world->CreateBody(&bodyDef);

  b2Vec2 edgeVert[4];
  edgeVert[0].Set(0, 0);
  edgeVert[1].Set(0, screenHeightMeters * 1.5);
  edgeVert[2].Set(numScreenWidths * screenWidthMeters, screenHeightMeters * 1.5);
  edgeVert[3].Set(numScreenWidths * screenWidthMeters, 0);
  bodyDef.position.Set(0.0f, 0.0f);
  b2ChainShape worldEdgeShape;
  worldEdgeShape.CreateChain(edgeVert, 4);

  b2FixtureDef chainFix;
  chainFix.shape = &worldEdgeShape;
  worldEdge->CreateFixture(&chainFix);

  //TODO: split ground up to have gaps
  bodyDef.position.Set(numScreenWidths * screenWidthMeters / 2, -1.0f);
  groundBody = world->CreateBody(&bodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(numScreenWidths * screenWidthMeters / 2, 1.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);
}

void PlayGameState::initDot() {
  b2BodyDef bodyDef;

  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.Set(18.0f, 12.0f);
  dotBody = world->CreateBody(&bodyDef);
  b2CircleShape dotShape;
  b2Vec2 dotPos(0.0f, 0.0f);
  dotShape.m_p = dotPos;
  dotShape.m_radius = dotRadius;

  b2FixtureDef dotFixture;
  dotFixture.shape = &dotShape;
  dotFixture.density = dotDensity;
  dotFixture.friction = dotFriction;
  dotBody->CreateFixture(&dotFixture);
}

void PlayGameState::update() {
  world->Step(timeStep, velocityIterations, positionIterations);
  trailPos.push_front(dotBody->GetPosition());
  if (trailPos.size() > numFadeCircles)
    trailPos.pop_back();

  if (!ofGetKeyPressed()) {
    float dampedHorVel = dotHorVelDampFactor * dotBody->GetLinearVelocity().x;
    dotBody->SetLinearVelocity(b2Vec2(dampedHorVel, dotBody->GetLinearVelocity().y));
  }

  //camera panning updates
  int dotPos = meterInPixels * dotBody->GetPosition().x;
  int diff = dotPos - (ofGetWindowWidth() / 2 + absCameraPos);
  if (diff > cameraPanDist && absCameraPos < absCameraMax) {
    absCameraPos += diff - cameraPanDist;
    absCameraPos = glm::min(absCameraMax, absCameraPos);
  } else if (diff < -cameraPanDist && absCameraPos > 0) {
    absCameraPos += diff + cameraPanDist;
    absCameraPos = glm::max((short) 0, absCameraPos);
  }
  relCameraPos = (absCameraPos % ((int) (ofGetWindowWidth() / bgRelSpeed))) * bgRelSpeed;
}

void PlayGameState::draw() {
  ofPushStyle();
    ofSetColor(ofColor::ghostWhite);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  ofPopStyle();
  background->draw(0 - relCameraPos, 0, ofGetWindowWidth(), ofGetWindowHeight() - groundOffset);
  wrapBackground->draw(ofGetWindowWidth() - relCameraPos, 0, ofGetWindowWidth(),
                       ofGetWindowHeight() - groundOffset);

  demoLevel.draw(absCameraPos);

  ofEnableAlphaBlending();
  int alpha = 255;
  int counter = 0;
  for (auto iter = trailPos.begin(); iter != trailPos.end(); ++iter) {
    ofSetColor(ofColor::mediumPurple, alpha -= 255 / numFadeCircles);
    drawDot(*iter, dotDrawRadius - fadeRadiusShrinkage / numFadeCircles * ++counter);
  }
  ofDisableAlphaBlending();
  ofSetColor(ofColor::white);
  drawDot(dotBody->GetPosition(), dotDrawRadius);
}

void PlayGameState::drawDot(b2Vec2 pos, float radius) {
  pos.x = meterInPixels * pos.x - absCameraPos;
  pos.y = ofGetWindowHeight() - meterInPixels * pos.y - groundOffset;
  ofSetCircleResolution(100);
  ofDrawCircle(pos.x, pos.y, radius);
}

void PlayGameState::keyPressed(int key) {
  float vertVel, horVel;
  switch (key) { //TODO: move to separate functions
  case 'a':
    vertVel = dotBody->GetLinearVelocity().y;
    if (dotBody->GetContactList() &&
      dotBody->GetContactList()->contact->IsTouching()) {
      dotBody->SetLinearVelocity(b2Vec2(-maxHorSpeed, vertVel));
    } else {
      horVel = dotBody->GetLinearVelocity().x;
      horVel -= horInc;
      horVel = std::max(-maxHorSpeed, horVel);
      dotBody->SetLinearVelocity(b2Vec2(horVel, vertVel));
    }
    break;
  case 'd':
    vertVel = dotBody->GetLinearVelocity().y;
    if (dotBody->GetContactList() &&
      dotBody->GetContactList()->contact->IsTouching()) {
      dotBody->SetLinearVelocity(b2Vec2(maxHorSpeed, vertVel));
    } else {
      horVel = dotBody->GetLinearVelocity().x;
      horVel +=  horInc;
      horVel = std::min(maxHorSpeed, horVel);
      dotBody->SetLinearVelocity(b2Vec2(horVel, vertVel));
    }
    break;
  case 'w': //TODO: plz fix
    if (dotBody->GetContactList() &&
        dotBody->GetContactList()->contact->IsTouching()) {
      dotBody->SetLinearVelocity(b2Vec2(dotBody->GetLinearVelocity().x, maxVertSpeed));
    }
    break;
  case ' ': //TODO: make double jump
    dotBody->SetLinearVelocity(b2Vec2(dotBody->GetLinearVelocity().x, maxVertSpeed));
    break;
  default:
    //quick test code here
    break;
  }
}

void PlayGameState::keyReleased(int key) {
  switch (key) {
  case 'w':
    break;
  default:
    break;
  }
}

std::vector<Clickable*> PlayGameState::getClickables() {
  return std::vector<Clickable*>(); //TODO: add return to menu clickable
}

void PlayGameState::clickOn(Clickable* button) {
  //TODO: add return to menu clickable
}

PlayGameState::~PlayGameState() {
  delete world;
  dotBody = NULL;
} 