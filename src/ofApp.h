#pragma once

#include "Box2D/Box2D.h"

#include "ofMain.h"
#include "audioEngine.h"

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