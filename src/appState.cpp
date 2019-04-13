#include "appState.h"
#include "ofMain.h"
#include "ofApp.h"

#include "glm/vec2.hpp"
#include <string>

//TODO: create constants / replace magic #s
std::string startMenuBgPath = "graphics/start_menu_background3.jpg";
std::string playGameBgPath = "graphics/dark3.jpg";

float timeStep = 1.0f / 60.0f;
int velocityIterations = 10;
int positionIterations = 8;


StartMenuState::StartMenuState() {
  background = new ofImage();
  background->load(startMenuBgPath);
}

void StartMenuState::update() {

}

void StartMenuState::draw() {
  if (background->isAllocated())
    background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

void StartMenuState::keyPressed(int key, AppState* currState) {
  currState->setNextState(new PlayGameState());
}

void StartMenuState::keyReleased(int key) {

}

StartMenuState::~StartMenuState() {
  delete background;
}

//-----------------------------------------------------------------------------
PlayGameState::PlayGameState() {
  background = new ofImage();
  background->load(playGameBgPath);

  initBox2DWorld();

  fadeBuffer = new ofFbo();
  fadeBuffer->allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
  fadeBuffer->begin();
    ofClear(255, 255, 255, 0);
  fadeBuffer->end();
}

void PlayGameState::initBox2DWorld() {
  b2Vec2 gravity(0.0f, -70.0f);
  world = new b2World(gravity);

  bodyDef.position.Set(0.0f, -10.0f);
  groundBody = world->CreateBody(&bodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);

  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 10.0f);
  dotBody = world->CreateBody(&bodyDef);
  b2CircleShape dotShape;
  b2Vec2 dotPos(0.0f, 0.0f);
  dotShape.m_p = dotPos;
  dotShape.m_radius = 1.0f;

  b2FixtureDef dotFixture;
  dotFixture.shape = &dotShape;
  dotFixture.density = 0.3f;
  dotFixture.friction = 0.1f;
  dotBody->CreateFixture(&dotFixture);
}

void PlayGameState::update() {
  world->Step(timeStep, velocityIterations, positionIterations);
  fadeBuffer->begin();
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, 45);
    background->draw(0, 0);
    ofDisableAlphaBlending();

    ofSetColor(255, 255, 255);
    b2Body* b = world->GetBodyList();
    b2Vec2 pos = b->GetPosition();
    ofSetColor(ofColor::azure);
    pos.x = ofGetWindowWidth() / 2 + 40.0f * pos.x;
    pos.y = ofGetWindowHeight() - 40.0f * pos.y;
    ofSetCircleResolution(100);
    ofDrawCircle(pos.x, pos.y, 40.0f);
  fadeBuffer->end();

  //replace with fn isOnGround()
  if (dotBody->GetContactList() && !ofGetKeyPressed()) {
    float dampedHorVel = 0.90 * dotBody->GetLinearVelocity().x;
    dotBody->SetLinearVelocity(b2Vec2(dampedHorVel, dotBody->GetLinearVelocity().y));
  }
}

void PlayGameState::draw() {
  if (background->isAllocated())
    background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

  fadeBuffer->draw(0, 0);
}

void PlayGameState::keyPressed(int key, AppState* currState) {
  float vertVel;
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
        wKeyPressed = true;
        dotBody->SetLinearVelocity(dotBody->GetLinearVelocity() + b2Vec2(0, 28));
      }
      break;
    default:
      //??
      ;
  }
}

void PlayGameState::keyReleased(int key) {
  switch (key) {
    case 'w':
      wKeyPressed = false;
      break;
    default:
      //??
      ;
  }
}

PlayGameState::~PlayGameState() {
  delete world;
  dotBody = NULL;
  groundBody = NULL;
}