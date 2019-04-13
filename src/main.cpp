#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1440, 960, OF_FULLSCREEN);
  ofSetWindowTitle("DOT: A Visual Experience");
  ofSetWindowPosition(OF_ALIGN_HORZ_CENTER, OF_ALIGN_VERT_CENTER);

  ofRunApp(new ofApp());
}