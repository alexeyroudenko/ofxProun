#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxProun.h"
#include "ofxCircleModule.h"

class ofApp : public ofBaseApp
{
public:
    proun::App proun;
        
    void setup();
    void create();
    void update();
    void draw();
    
    proun::FboNode *node;
    
    void keyPressed(int key);
};
