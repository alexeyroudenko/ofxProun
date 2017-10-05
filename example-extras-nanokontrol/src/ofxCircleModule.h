#pragma once

#include "ofxProun.h"
#include "prounFboNode.h"

class ofxCircleModule: public proun::FboNode
{
protected:
    ofVec2f dimensions;
public:
    ofParameter<float> radius;
    ofParameter<float> count;
    ofParameter<float> rotation;
    
    ofxCircleModule():dimensions(1280.f, 720.f) {
        settings = new ofParameterGroup();
        settings->setName("circle");
        settings->add(radius.set("radius", 0.5,0,1));
        settings->add(count.set("count", 16,3,64));
        settings->add(rotation.set("rotation", 0,0,360));
        
        ofLogVerbose("ofxCircleModule", "setup" + settings->getName());
        
        fbo.allocate(dimensions.x, dimensions.y, GL_RGBA);
    }
    
    void setup() {
    }
    
    void update() {
        fbo.begin();
        ofClear(0);
        ofSetCircleResolution(count);
        ofTranslate(fbo.getWidth() / 2, fbo.getHeight() / 2);
        ofRotateZ(rotation);
        ofDrawCircle(0, 0, radius * fbo.getHeight() / 2);
        fbo.end();
        
        ofSetCircleResolution(32);
    }
};
