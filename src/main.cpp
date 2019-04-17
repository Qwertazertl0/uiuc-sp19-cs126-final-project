#include "ofMain.h"
#include "ofApp.h"
#include "../resource.h"

//========================================================================
int main( ){
  ofGLFWWindowSettings settings;
  settings.windowMode = OF_WINDOW;
  settings.setSize(1440, 960);
  settings.resizable = false;
  settings.title = "DOT: A Visual Experience";
  settings.setPosition(glm::vec2(0, 38)); //title bar is 38 pixels
  ofCreateWindow(settings);

  ofRunApp(new ofApp());
}