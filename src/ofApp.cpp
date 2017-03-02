#include "LRF.h"
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//settings
	ofSetWindowShape(800, 600);//set window size
	//ofToggleFullscreen();//full screen
	ofSetFrameRate(60);
	ofEnableAlphaBlending();//use opacity
	ofBackground(0, 0, 0);

	//all obj setup
	allobj.setup();
	//lrf = new LRF();
	//lrf->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	//test using mouse
	
	vector<ofVec2f> vec;
	vec.emplace_back(ofGetMouseX()-ofGetWidth()/2,-ofGetMouseY()+ofGetHeight()/2);
	allobj.update(vec);
	
	//using lrf
	//allobj.update(lrf->update());
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofScale(1, -1);
	//window grid
	/*
	ofSetLineWidth(10);
	ofSetColor(255, 255, 255);//255, 255, 2550,0,0
	ofLine(0, ofGetHeight() / 2, 0, -ofGetHeight() / 2);
	ofLine(ofGetWidth() / 2, 0, -ofGetWidth() / 2, 0);
	*/
	//draw obj
	allobj.draw();
	//draw LRF point
	//lrf->draw();	
}

void ofApp::exit() {
	//lrf->end_LRF();
}
void ofApp::keyPressed(int key)
{
}
void ofApp::keyReleased(int key)
{
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
