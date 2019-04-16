#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
  ofGLFWWindowSettings settings;
  settings.windowMode = OF_WINDOW;
  settings.setSize(1440, 960);
  settings.resizable = false;
  ofCreateWindow(settings);

  ofSetWindowPosition(OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_CENTER);
  ofSetWindowTitle("DOT: A Visual Experience");
  ofRunApp(new ofApp());
}