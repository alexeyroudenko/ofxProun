#pragma once
#include "ofMain.h"
#include "prounModel.h"

namespace proun {
    
    class SelectionController
    {
    public:
        Model *model;
        
        bool doSelection;
        bool makeSelection;
        ofPoint startPosition;
        ofPoint current;
        ofRectangle rect;
        void setup(Model *model_);
        void draw();
        void start();
        void finish();
        
        void mouseDragged(ofMouseEventArgs &e);
        void mousePressed(ofMouseEventArgs &e);
        void mouseReleased(ofMouseEventArgs &e);
        void mouseScrolled(ofMouseEventArgs &e){};
        void mouseEntered(ofMouseEventArgs &e){};
        void mouseExited(ofMouseEventArgs &e){};
        void updateRectangle();
        void deselectAll();
        void onLoad(string &fileName);
    };
    
}
