#pragma once

#include "Box2D/Box2D.h"

#include "ofMain.h"
#include "audioEngine.h"

//Abstract class representing each "screen" (e.g. start menu, settings, about)
class AppState {
  public:
    virtual void update() {}
    virtual void draw() {}
    virtual void keyPressed(int key, AppState* currState) {}
    virtual void keyReleased(int key) {}
    void setNextState(AppState* state) {
      nextState = state;
    }

    AppState* nextState = this;
};

//Wrapper class linking graphic images to simple ofRectangle to create clickable buttons
class Clickable {
  public:
    Clickable(ofImage* neutral, ofImage* hover, ofRectangle* pos) :
              neutralImage(neutral), hoverImage(hover), position(pos) {}
    ~Clickable();
    void draw();
    bool inside(glm::vec2 mousePos);

    ofImage* neutralImage;
    ofImage* hoverImage;
    ofRectangle* position;
};

//Main application class run from main.cpp
class ofApp : public ofBaseApp {
	public:
		void setup();
		void exit();

		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);	

		AudioEngine* audioEng;
    AppState* gameState;
};