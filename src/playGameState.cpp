#include "playGameState.h"
#include "ofMain.h"
#include "Box2D\Box2D.h"
#include <algorithm>

PlayGameState::PlayGameState(bool jumpLimit, int sliderX) {
  background = new ofImage(playGameBgPath);
  wrapBackground = new ofImage(playGameBgPath);
  instructions = new ofImage(instructionsPath);
  
  ofImage* neutralPath = new ofImage(homeNeutralPath);
  ofImage* hoverPath = new ofImage(homeHoverPath);
  int s = homeButtonSideLength;
  ofRectangle* loc = new ofRectangle(ofGetWindowWidth() - s - cornerOffset, cornerOffset, s, s);
  homeButton = new Clickable(neutralPath, hoverPath, loc);

  jumpLimitOn = jumpLimit;
  sliderXPos = sliderX;
  initBox2DWorld();
  initGameParticles();
}

void PlayGameState::initBox2DWorld() {
  world = new b2World(gravity);
  initStaticBodies();
  initDot();
}

void PlayGameState::initGameParticles() {
  //Future extension of particle system, if desired
}

void PlayGameState::initStaticBodies() {
  b2BodyDef bodyDef;

  //platforms
  for (int i = 0; i < numBodies; ++i) {
    StaticRect p(bodyWidths[i], bodyHeights[i], bodyCenterX[i], bodyCenterY[i], world);
    demoLevel.platforms.push_back(p);
  }

  StaticPolygon hill(hillVertices, world);
  StaticPolygon endPlatform(endPlat, world);
  demoLevel.hills.push_back(hill);
  demoLevel.hills.push_back(endPlatform);

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

  //ground pieces
  initGround();
}

void PlayGameState::initGround() {
  b2BodyDef bodyDef;

  for (int i = 0; i < 2 * numGroundPieces; i += 2) {
    b2Body* groundBody;
    bodyDef.position.Set((groundBounds[i] + groundBounds[i + 1]) / 2, -1.0f);
    groundBody = world->CreateBody(&bodyDef);
    b2PolygonShape groundBox;
    float* width = new float;
    *width = groundBounds[i + 1] - groundBounds[i];
    groundBox.SetAsBox(*width / 2, 1.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);
    groundBody->SetUserData(width);
    groundBodies.push_back(groundBody);
  }
}

void PlayGameState::initDot() {
  b2BodyDef bodyDef;

  bodyDef.type = b2_dynamicBody;
  bodyDef.fixedRotation = true;
  bodyDef.position.Set(dotInitPos.x, dotInitPos.y);
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

void PlayGameState::resetDot() {
  trailPos.clear();
  world->DestroyBody(dotBody);
  initDot();
}

void PlayGameState::update() {
  //reset if necessary
  if (dotBody->GetPosition().y < dotResetHeight) {
    resetDot();
  }
   
  //process game physics
  if (ofGetKeyPressed('a')) {
    pressA();
  } else if (ofGetKeyPressed('d')) {
    pressD();
  }

  world->Step(timeStep, velocityIterations, positionIterations);
  trailPos.push_front(dotBody->GetPosition());
  if (trailPos.size() > numFadeCircles)
    trailPos.pop_back();

  //damping and jump logic
  if (!ofGetKeyPressed()) {
    float dampedHorVel;
    if (isInAir()) {
      dampedHorVel = inAirHorVelDampFactor * dotBody->GetLinearVelocity().x;
    } else {
      dampedHorVel = dotHorVelDampFactor * dotBody->GetLinearVelocity().x;
    }
    dotBody->SetLinearVelocity(b2Vec2(dampedHorVel, dotBody->GetLinearVelocity().y));
  }

  if (!isInAir()) {
    jumped = false;
  }

  //camera panning updates
  int dotPos = pixelsPerMeter * dotBody->GetPosition().x;
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
  //draw ground and backgrounds
  ofPushStyle();
    ofSetColor(ofColor::black);
    ofDrawRectangle(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(themePurple);
    ofSetRectMode(OF_RECTMODE_CENTER);
    for (b2Body* groundPiece : groundBodies) {
      float x = groundPiece->GetPosition().x * pixelsPerMeter - absCameraPos;
      float* w = (float*) groundPiece->GetUserData();
      ofDrawRectangle(x, ofGetWindowHeight() - groundOffset / 2, (*w)*pixelsPerMeter, groundOffset);
    }
  ofPopStyle();
  background->draw(0 - relCameraPos, 0, ofGetWindowWidth(), ofGetWindowHeight() - groundOffset);
  wrapBackground->draw(ofGetWindowWidth() - relCameraPos, 0, ofGetWindowWidth(),
                       ofGetWindowHeight() - groundOffset);
  //draw platforms
  demoLevel.draw(absCameraPos);

  //draw dot and trails
  ofEnableAlphaBlending();
  int alpha = 255;
  int counter = 0;
  for (auto iter = trailPos.begin(); iter != trailPos.end(); ++iter) {
    ofSetColor(ofColor::mediumPurple, alpha -= 255 / numFadeCircles);
    drawDot(*iter, dotDrawRadius - fadeRadiusShrinkage / numFadeCircles * ++counter);
  }
  ofSetColor(ofColor::white);
  drawDot(dotBody->GetPosition(), dotDrawRadius);

  homeButton->draw();

  //draw instructions
  if (instructionLifeCounter < instructionLifeLimit) {
    ofPushStyle();
      int alpha = glm::min(255, fadeDec * (instructionLifeLimit - instructionLifeCounter));
      ofSetColor(themePurple, alpha);
      ofSetRectMode(OF_RECTMODE_CENTER);
      instructions->draw(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);
    ofPopStyle();
    ++instructionLifeCounter;
  }
  ofDisableAlphaBlending();
}

void PlayGameState::drawDot(b2Vec2 pos, float radius) {
  pos.x = pixelsPerMeter * pos.x - absCameraPos;
  pos.y = ofGetWindowHeight() - pixelsPerMeter * pos.y - groundOffset;
  ofSetCircleResolution(circleResolution);
  ofDrawCircle(pos.x, pos.y, radius);
}

void PlayGameState::keyPressed(int key) {
  switch (key) {
  case 'w':
    pressW();
    break;
  case ' ':
    pressSpace();
    break;
  default:
    break;
  }
}

void PlayGameState::pressA() {
  float vertVel, horVel;

  vertVel = dotBody->GetLinearVelocity().y;
  if (dotBody->GetContactList() &&
    dotBody->GetContactList()->contact->IsTouching()) {
    dotBody->SetLinearVelocity(b2Vec2(-maxHorSpeed, vertVel));
  }
  else {
    horVel = dotBody->GetLinearVelocity().x;
    horVel -= horInc;
    horVel = std::max(-maxHorSpeed, horVel);
    dotBody->SetLinearVelocity(b2Vec2(horVel, vertVel));
  }
}

void PlayGameState::pressD() {
  float vertVel, horVel;

  vertVel = dotBody->GetLinearVelocity().y;
  if (dotBody->GetContactList() &&
    dotBody->GetContactList()->contact->IsTouching()) {
    dotBody->SetLinearVelocity(b2Vec2(maxHorSpeed, vertVel));
  }
  else {
    horVel = dotBody->GetLinearVelocity().x;
    horVel += horInc;
    horVel = std::min(maxHorSpeed, horVel);
    dotBody->SetLinearVelocity(b2Vec2(horVel, vertVel));
  }
}

void PlayGameState::pressW() {
  if (!isInAir()) {
    dotBody->SetLinearVelocity(b2Vec2(dotBody->GetLinearVelocity().x, maxVertSpeed));
    ofApp::audioEng->playJump('w');
  }
}

void PlayGameState::pressSpace() {
  if (!jumpLimitOn || (isInAir() && !jumped)) {
    dotBody->SetLinearVelocity(b2Vec2(dotBody->GetLinearVelocity().x, maxVertSpeed));
    jumped = true;
    ofApp::audioEng->playJump(' ');
  }
}

bool PlayGameState::isInAir() {
  for (auto con = dotBody->GetContactList(); con != nullptr; con = con->next) {
    if (con->contact->IsTouching()) {
      b2Vec2 contactNormal = con->contact->GetManifold()->localNormal;
      if (contactNormal.y > airborneYDiffContactLimit) {
        return false;
      }
    }
  }
  return true;
}

std::vector<Clickable*> PlayGameState::getClickables() {
  return std::vector<Clickable*>({homeButton});
}

void PlayGameState::clickOn(Clickable* button) {
  if (button == homeButton) {
    nextState = new StartMenuState(jumpLimitOn, sliderXPos);
  }
}

PlayGameState::~PlayGameState() {
  delete world;
  delete background;
  delete wrapBackground;
  delete instructions;
  delete homeButton;
  dotBody = NULL;
} 