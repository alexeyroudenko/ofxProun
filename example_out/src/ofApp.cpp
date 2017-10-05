#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofParameterGroup *settings = new ofParameterGroup();
    settings->setName("settings");
    settings->add(width.set("width", 0.5, 0.0, 1.0));
    settings->add(height.set("height", 0.5, 0.0, 1.0));
    
    proun.setup("proun.csv");
    proun.addNode(settings, true);
    proun.load();
}

//--------------------------------------------------------------
void ofApp::update() {
	proun.update();
    
    width = abs(sin(ofGetElapsedTimef()));
}

//--------------------------------------------------------------
void ofApp::draw() {

    proun.drawBackground();
    
    ofPushMatrix();
    ofSetColor(128);
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    ofDrawBox(ofGetWidth() * width, ofGetHeight() * height, 1);
    ofPopMatrix();
    ofSetColor(255);
    
	proun.draw();
    
    proun.drawInfo();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}
