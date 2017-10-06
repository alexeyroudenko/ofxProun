#include "ofApp.h"
#include "prounExtrasFactory.h"
#include "prounPresetsModule.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    node = new ofxCircleModule();
    
    proun.setup("proun.csv");
    proun.model->factory = new proun::ExtrasFactory();
    proun.addNode(node);
    proun.initModules();
    
    PresetsModule *presets = new PresetsModule();
    proun.model->modules->add(presets);
    proun.addNode(presets->presets->model->settings);
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
