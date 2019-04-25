#include "startMenuState.h"
#include "playGameState.h"
#include "ofApp.h"

StartMenuState::StartMenuState(bool jumpLimit) {
  StartMenuState();
  jumpLimitOn = jumpLimit;
}

StartMenuState::StartMenuState() {
  background = new ofImage(startMenuBgPath);
  logo = new ofImage(logoPath);
  aboutText = new ofImage(aboutTextPath);
  volumeText = new ofImage(volTextPath);
  volumeBar = new ofImage(volBarPath);
  jumpLimitText = new ofImage(jumpLimitPath);

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

  neutralPath = new ofImage(sliderPath);
  hoverPath = neutralPath;
  loc = new ofRectangle(sliderX, sliderY, sliderWidth, sliderHeight);
  slider = new Clickable(neutralPath, hoverPath, loc);

  ofApp::partSystem->clear();
  ofApp::partSystem->init(numInitParticles, initVel);
  jumpLimitOn = true;
}

void StartMenuState::update() {
  if (!mouseOnButton && isMouseOnButton()) {
    ofApp::audioEng->playMouseOver();
    mouseOnButton = true;
  } else if (mouseOnButton && !isMouseOnButton()) {
    mouseOnButton = false;
  }

  if (drawItems == OPTIONS && sliderSelected) {
    sliderX = ofGetMouseX();
    sliderX = glm::max(volBarX - sliderWidth / 2, sliderX);
    sliderX = glm::min(sliderX, sliderDefaultX);
    slider->getPosition()->setX(sliderX);

    float percentVol = (sliderX - volBarX + sliderWidth / 2) / (float) volBarWidth;
    ofApp::audioEng->setVolume(percentVol);
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
      ofSetCircleResolution(logoCircleResolution);
      ofDrawCircle(logoCirclePos, logoCircleRadius);
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

    ofPushStyle();
      ofSetColor(volumeBarColor);
      ofDrawRectangle(volBarX, volBarY, sliderX - volBarX + sliderWidth / 2, volBarHeight);
    ofPopStyle();
    volumeBar->draw(volBarX, volBarY);
    slider->draw();
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
        return std::vector<Clickable*>({returnButton, onButton, slider});
      } else {
        return std::vector<Clickable*>({returnButton, offButton, slider});
      }
      break;
    case ABOUT:
      return std::vector<Clickable*>({returnButton});
      break;
    default:
      return std::vector<Clickable*>();
  }
}

void StartMenuState::mousePressed() {
  if (sliderSelected && !isMouseOnButton()) {
    sliderSelected = false;
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
      if (sliderSelected) {
        sliderSelected = false;
        break;
      }

      if (button == returnButton) {
        drawItems = MENU;
      } else if (button == onButton) {
        jumpLimitOn = false;
      } else if (button == offButton) {
        jumpLimitOn = true;
      } else if (button == slider) {
        sliderSelected = true;
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
  delete volumeBar;
  delete jumpLimitText;

  delete startButton;
  delete optionsButton;
  delete aboutButton;
  delete quitButton;
  delete returnButton;
  delete onButton;
  delete offButton;
  delete slider;
}