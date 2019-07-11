#pragma once
#include "prounModel.h"
#include "prounSettings.h"
#include "prounSelectionController.h"

namespace proun {
    
    class MouseController
    {
    public:
        
        Model *model;
        Node::TempConnection tempConnection;
        SelectionController selection;
        ofPoint lastMouse;
        
        void setup(Model *model_);    
        void draw();
        void enable();
        void disable();
        
        /* --------------------------------------------------------------
         # ofxProun::Mouse
         #
         #
         #
         # -------------------------------------------------------------- */
        void mousePressed(ofMouseEventArgs &e);
        void mouseMoved(ofMouseEventArgs &e);
        void mouseDragged(ofMouseEventArgs &e);
        void mouseReleased(ofMouseEventArgs &e);
        void mouseScrolled(ofMouseEventArgs &e);
        void mouseEntered(ofMouseEventArgs &e);
        void mouseExited(ofMouseEventArgs &e);
       
    };
    
}
