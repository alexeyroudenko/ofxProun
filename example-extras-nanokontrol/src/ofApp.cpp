#include "ofApp.h"
#define PROUN_EXTRAS

#ifdef PROUN_EXTRAS
#include "prounExtrasFactory.h"
#endif

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    node = new ofxCircleModule();
    
    proun.setup("proun.csv");
//#ifdef PROUN_EXTRAS
//    proun.model->factory = new proun::ExtrasFactory();
//#endif
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
