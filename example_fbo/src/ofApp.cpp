#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    node = new ofxCircleModule();
    ofLogVerbose("ofApp", "setup" + node->settings->getName());
    
    proun.setup("proun.csv");
    proun.addNode(node);
    proun.load();
}

//--------------------------------------------------------------
void ofApp::update() {
	proun.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    proun.drawBackground();
    
    int padding = 50;
    ofRectangle rect(padding,
                     padding,
                     ofGetWidth() - padding,
                     ofGetHeight() - padding);
    
    node->fbo.draw(rect);
    
	proun.draw();
    proun.drawInfo();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
