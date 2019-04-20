#include "playGameState.h"
#include "ofMain.h"
#include "Box2D\Box2D.h"

PlayGameState::PlayGameState() {
  background = new ofImage();
  background->load(playGameBgPath);
  wrapBackground = new ofImage();
  wrapBackground->load(playGameBgPath);

  initBox2DWorld();
}

void PlayGameState::initBox2DWorld() {
  world = new b2World(gravity);

  //TODO: finalize init positions
  bodyDef.position.Set(0.0f, -10.0f);
  groundBody = world->CreateBody(&bodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);

  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.Set(0.0f, 10.0f);
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
}

void PlayGameState::draw() {
  background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  
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
  pos.x = ofGetWindowWidth() / 2 + meterInPixels * pos.x;
  pos.y = ofGetWindowHeight() - meterInPixels * pos.y;
  ofSetCircleResolution(100);
  ofDrawCircle(pos.x, pos.y, radius);
}

void PlayGameState::keyPressed(int key, AppState* currState) {
  float vertVel;
  //TODO: redo left and right movements
  switch (key) {
  case 'a':
    vertVel = dotBody->GetLinearVelocity().y;
    dotBody->SetLinearVelocity(b2Vec2(-20, vertVel));
    break;
  case 'd':
    vertVel = dotBody->GetLinearVelocity().y;
    dotBody->SetLinearVelocity(b2Vec2(20, vertVel));
    break;
  case 'w':
    if (dotBody->GetContactList() &&
      dotBody->GetContactList()->contact->IsTouching()) {
      dotBody->SetLinearVelocity(dotBody->GetLinearVelocity() + b2Vec2(0, 28));
    }
    break;
  default:
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
  groundBody = NULL;
}