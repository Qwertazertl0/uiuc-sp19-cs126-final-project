#include "startMenuState.h"
#include "playGameState.h"
#include "ofMain.h"
#include "ofApp.h"

#include <string>

//Graphics image paths
std::string startMenuBgPath = "graphics/start_menu_background4.jpg";
std::string logoPath = "graphics/dotLogo.png";

std::string startNeutralPath = "graphics/startNeutral.png";
std::string startHoverPath = "graphics/startHover.png";
std::string optionsNeutralPath = "graphics/optionsNeutral.png";
std::string optionsHoverPath = "graphics/optionsHover.png";
std::string aboutNeutralPath = "graphics/aboutNeutral.png";
std::string aboutHoverPath = "graphics/aboutHover.png";
std::string quitNeutralPath = "graphics/quitNeutral.png";
std::string quitHoverPath = "graphics/quitHover.png";
std::string returnNeutralPath = "graphics/backNeutral.png";
std::string returnHoverPath = "graphics/backHover.png";

StartMenuState::StartMenuState() {
  background = new ofImage();
  background->load(startMenuBgPath);
  logo = new ofImage();
  logo->load(logoPath);

  ofImage* neutralPath = new ofImage(startNeutralPath);
  ofImage* hoverPath = new ofImage(startHoverPath);
  ofRectangle* loc = new ofRectangle(0, startYCoord, menuButtonWidth, menuButtonHeight);
  startButton = new Clickable(neutralPath, hoverPath, loc);

  neutralPath = new ofImage(optionsNeutralPath);
  hoverPath = new ofImage(optionsHoverPath);
  loc = new ofRectangle(0, optionsYCoord, menuButtonWidth, menuButtonHeight);
  optionsButton = new Clickable(neutralPath, hoverPath, loc);

  neutralPath = new ofImage(aboutNeutralPath);
  hoverPath = new ofImage(aboutHoverPath);
  loc = new ofRectangle(0, aboutYCoord, menuButtonWidth, menuButtonHeight);
  aboutButton = new Clickable(neutralPath, hoverPath, loc);

  neutralPath = new ofImage(quitNeutralPath);
  hoverPath = new ofImage(quitHoverPath);
  loc = new ofRectangle(0, quitYCoord, menuButtonWidth, menuButtonHeight);
  quitButton = new Clickable(neutralPath, hoverPath, loc);

  neutralPath = new ofImage(returnNeutralPath);
  hoverPath = new ofImage(returnHoverPath);
  loc = new ofRectangle(returnXCoord, returnYCoord, returnWidth, returnHeight);
  returnButton = new Clickable(neutralPath, hoverPath, loc);

  ofApp::partSystem->init(numInitParticles, initVel);
}

void StartMenuState::update() {
  if (!mouseOnButton && isMouseOnButton()) {
    ofApp::audioEng->playMouseOver();
    mouseOnButton = true;
  } else if (mouseOnButton && !isMouseOnButton()) {
    mouseOnButton = false;
  }

  ofApp::partSystem->updateParticles();
}

void StartMenuState::draw() {
  background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  ofApp::partSystem->draw();
  if (drawItems == MENU) {
    ofPushStyle();
      ofSetColor(ofColor::blanchedAlmond);
      ofSetCircleResolution(100);
      ofDrawCircle(glm::vec2(375, 170), 31); //TODO: pull to constant
    ofPopStyle();
    logo->draw(logoCornerOffset, logoCornerOffset);
    startButton->draw();
    optionsButton->draw();
    aboutButton->draw();
    quitButton->draw();
  } else {
    returnButton->draw();
  }
}

bool StartMenuState::isMouseOnButton() {
  for (Clickable* button : getClickables()) {
    if (button->inside(glm::vec2(ofGetMouseX(), ofGetMouseY()))) {
      return true;
    }
  }
  return false;
}

std::vector<Clickable*> StartMenuState::getClickables() {
  switch (drawItems) {
    case MENU:
      return std::vector<Clickable*>({startButton, optionsButton, aboutButton, quitButton});
      break;
    case OPTIONS:
      return std::vector<Clickable*>({returnButton});
      break;
    case ABOUT:
      return std::vector<Clickable*>({returnButton});
      break;
    default:
      return std::vector<Clickable*>();
  }
}

void StartMenuState::clickOn(Clickable* button) {
  switch (drawItems) {
    case MENU:
      if (button == startButton) {
        nextState = new PlayGameState();
      } else if (button == optionsButton) {
        drawItems = OPTIONS;
      } else if (button == aboutButton) {
        drawItems = ABOUT;
      } else if (button == quitButton) {
        nextState = nullptr;
      }
      break;
    case OPTIONS:
      drawItems = MENU;
      break;
    case ABOUT:
      drawItems = MENU;
      break;
    default:
      return;
  }
}

StartMenuState::~StartMenuState() {
  delete background;
  delete startButton;
  delete optionsButton;
  delete aboutButton;
  delete quitButton;
}