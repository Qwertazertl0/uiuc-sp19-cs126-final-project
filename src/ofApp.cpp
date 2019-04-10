#include <iostream>

#include "ofApp.h"
#include "soloud.h"
#include "soloud_wav.h"

SoLoud::Soloud* gSoloud;
SoLoud::Wav* gWav;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetEscapeQuitsApp(false);
	gSoloud = new SoLoud::Soloud;
	gWav = new SoLoud::Wav;

	std::cout << gSoloud->init() << std::endl;
	std::cout << gWav->load("data/test_bach.wav") << std::endl;
}

void ofApp::exit() {
	std::cout << "Exiting..." << std::endl;
	gSoloud->deinit();
	delete gWav;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawRectangle(0, 0, 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	int handle = gSoloud->play(*gWav);
	std::cout << handle << std::endl;
	std::cout << gSoloud->getActiveVoiceCount() << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
