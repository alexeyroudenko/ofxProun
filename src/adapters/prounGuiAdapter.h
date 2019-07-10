#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "prounModel.h"

namespace proun {
    class GuiAdapter {
    protected:
        Model *model;
        
    public:
        ofParameter<bool> doGui;
        void setup(Model *model_);
        void addNode(ofParameterGroup *settings, bool isOutput = false);
        void draw();
        void load();
        void save();
        
    protected:
        
        vector<ofPtr<ofParameterGroup>> ptrs;
        map<string, ofxPanel*>  guis;
        string selected = "";
        int i = 0;
        
        /* --------------------------------------------------------------
         # events
         #
         #
         #
         # -------------------------------------------------------------- */
        void onSelect(proun::Model::prounEventArgs &e);
        void onDeSelect(proun::Model::prounEventArgs &e);
        void onMove(proun::Model::prounEventArgs &e);
    };
}
