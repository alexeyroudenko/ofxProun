#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "prounPresets.h"

namespace ofxPresets {
        
    class Gui {
        
    public:
                
        void setup(int count) {
            ofLogVerbose("ofxPresets", "setup " + ofToString(count));
            
            initControls();
        }
        
        void initControls() {
        }
        
        void update() {
        }
        
        void setVisible(bool visible) {
        }
        
        void draw() {
        }
    };
}
