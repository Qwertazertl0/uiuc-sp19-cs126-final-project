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
}

void StartMenuState::update() {
  //TODO: Keep for particle system later
}

void StartMenuState::draw() {
  if (background->isAllocated())
    background->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
  if (logo->isAllocated())
    logo->draw(logoCornerOffset, logoCornerOffset);
  startButton->draw();
  optionsButton->draw();
  aboutButton->draw();
  quitButton->draw();

  ofSetColor(ofColor::blanchedAlmond);
  ofSetCircleResolution(100);
  ofDrawCircle(glm::vec2(375, 170), 31);
  ofSetColor(ofColor::white);
}

std::vector<Clickable*> StartMenuState::getClickables() {
  return std::vector<Clickable*>({startButton, optionsButton, aboutButton, quitButton});
}

void StartMenuState::clickOn(Clickable* button) {
  if (button == startButton) {
    nextState = new PlayGameState();
  } else if (button == optionsButton) {
    std::cout << "options" << std::endl; //TODO: options screen
  } else if (button == aboutButton) {
    std::cout << "about" << std::endl; //TODO: about screen
  } else if (button == quitButton) {
    ofExit(0);
  }
}

StartMenuState::~StartMenuState() {
  delete background;
  delete startButton;
  delete optionsButton;
  delete aboutButton;
  delete quitButton;
}