#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxProun.h"

class ofApp : public ofBaseApp
{
public:
    proun::App proun;
    
    ofParameter<float> width;
    ofParameter<float> height;
    
    void setup();
    void create();
    void update();
    void draw();
    
    void keyPressed(int key);
};
