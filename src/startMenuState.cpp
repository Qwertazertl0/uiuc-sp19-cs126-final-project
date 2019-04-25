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

std::string volTextPath = "graphics/volumeText.png";
std::string jumpLimitPath = "graphics/jumpLimitText.png";
std::string onNeutralPath = "graphics/onNeutral.png";
std::string onHoverPath = "graphics/onHover.png";
std::string offNeutralPath = "graphics/offNeutral.png";
std::string offHoverPath = "graphics/offHover.png";
std::string aboutTextPath = "graphics/aboutText.png";

StartMenuState::StartMenuState() {
  background = new ofImage();
  background->load(startMenuBgPath);
  logo = new ofImage();
  logo->load(logoPath);
  aboutText = new ofImage();
  aboutText->load(aboutTextPath);
  volumeText = new ofImage();
  volumeText->load(volTextPath);
  jumpLimitText = new ofImage();
  jumpLimitText->load(jumpLimitPath);

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

  neutralPath = new ofImage(onNeutralPath);
  hoverPath = new ofImage(onHoverPath);
  loc = new ofRectangle(onOffX, onOffY, onOffWidth, onOffHeight);
  onButton = new Clickable(neutralPath, hoverPath, loc);

  neutralPath = new ofImage(offNeutralPath);
  hoverPath = new ofImage(offHoverPath);
  loc = new ofRectangle(onOffX, onOffY, onOffWidth, onOffHeight);
  offButton = new Clickable(neutralPath, hoverPath, loc);

  ofApp::partSystem->clear();
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
  ofEnableAlphaBlending();
  if (drawItems == MENU) {
    ofPushStyle();
      ofSetColor(ofColor::white);
      ofSetCircleResolution(100);
      ofDrawCircle(glm::vec2(375, 170), 30); //TODO: pull to constant
    ofPopStyle();
    logo->draw(logoCornerOffset, logoCornerOffset);
    startButton->draw();
    optionsButton->draw();
    aboutButton->draw();
    quitButton->draw();
  } else if (drawItems == ABOUT) {
    aboutText->draw(aboutTextX, aboutTextY);
    returnButton->draw();
  } else {
    if (jumpLimitOn) {
      onButton->draw();
    } else {
      offButton->draw();
    }
    volumeText->draw(volTextX, volTextY);
    jumpLimitText->draw(jumpLimX, jumpLimY);
    returnButton->draw();
  }
  ofDisableAlphaBlending();
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
      if (jumpLimitOn) {
        return std::vector<Clickable*>({returnButton, onButton});
      } else {
        return std::vector<Clickable*>({returnButton, offButton});
      }
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
        nextState = new PlayGameState(jumpLimitOn);
      } else if (button == optionsButton) {
        drawItems = OPTIONS;
      } else if (button == aboutButton) {
        drawItems = ABOUT;
      } else if (button == quitButton) {
        nextState = nullptr;
      }
      break;
    case OPTIONS:
      if (button == returnButton) {
        drawItems = MENU;
      } else if (button == onButton) {
        jumpLimitOn = false;
      } else if (button == offButton) {
        jumpLimitOn = true;
      }
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
  delete logo;
  delete aboutText;
  delete volumeText;
  delete jumpLimitText;

  delete startButton;
  delete optionsButton;
  delete aboutButton;
  delete quitButton;
  delete returnButton;
  delete onButton;
  delete offButton;
}