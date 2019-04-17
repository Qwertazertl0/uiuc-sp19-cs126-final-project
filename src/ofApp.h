#pragma once

#include "Box2D/Box2D.h"

#include "ofMain.h"
#include "audioEngine.h"

//Wrapper class linking graphic images to simple ofRectangle to create clickable buttons
class Clickable {
    ofImage* neutralImage;
    ofImage* hoverImage;
    ofRectangle* position;
  public:
    Clickable(ofImage* neutral, ofImage* hover, ofRectangle* pos) :
              neutralImage(neutral), hoverImage(hover), position(pos) {}
    ~Clickable();
    void draw();
    bool inside(glm::vec2 mousePos);
};

//Abstract class representing each "screen" (e.g. start menu, settings, about)
class AppState {
  public:
    virtual void update() {}
    virtual void draw() {}
    virtual void keyPressed(int key, AppState* currState) {} //TODO: passing in currState is weird, find better workaround
    virtual void keyReleased(int key) {}
    virtual std::vector<Clickable*> getClickables() {return std::vector<Clickable*>();};
    virtual void clickOn(Clickable* button) {}
    void setNextState(AppState* state) {
      nextState = state;
    }

    AppState* nextState = this;
};

//Main application class run from main.cpp
class ofApp : public ofBaseApp {
    int mousePressInitPosX;
    int mousePressInitPosY;
	public:
		void setup();
		void exit();

		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    static AudioEngine* audioEng;
    AppState* gameState;
};