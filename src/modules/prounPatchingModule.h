#pragma once

#include "prounModel.h"
#include "prounModule.h"
#include "prounSettings.h"

namespace proun {
    
    class PatchingModule:public Module
    {
    protected:
        
    public:
        
        virtual void setup() {};
        
        virtual void update(){};
        
        virtual void draw(){};
        
        virtual bool doPresets() {
            return false;
        };
        
        string getInfo() {
            return "[patching]" + getHelpString();;
        }
        
        void keyPressed(int key) {}
        
        string getHelpString() {
            stringstream help;
            help << "\n\n[ofxProun]:\n";
            help << "[`] toggle shift\n";
            help << "[s] save patch\n";
            help << "[l] load patch\n";
            help << "[n] clear patch\n";
            help << "[g] toggle all guis (" + ofToString(Settings::getInstance().showGUIS) + ")\n";
            help << "[m] toggle moves (" + ofToString(Settings::getInstance().doMoves) + ")\n";
            help << "[DEL]: delete node\n\n";
            return help.str();
        }
        
    };
    
};



