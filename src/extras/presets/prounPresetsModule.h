#pragma once

#include "prounModule.h"
#include "prounNanokontrolNode.h"
#include "prounNanokontrolNode.h"
#include "prounPresetsController.h"

namespace proun {
    
    class PresetsModule:public Module
    {
        bool doSave = false;
    public:
        
        ofxPresets::Controller *presets;
        
        PresetsModule() {
            presets = new ofxPresets::Controller();
        };
        
        virtual bool doPresets() {
            return true;
        };
      
        virtual void setup() {
            
        };
        
        virtual void update() {
            presets->model->update();
         };
        
        virtual void draw() {
            
        };
        
        string getInfo() {
            stringstream help;
            help << "\n\n[presets]:\n";
            help << "[1-5] load preset\n";
            help << "[u] toggle state\n";
            help << (doSave == true ? "saving\n" : "loading\n");
            return help.str();
        }
        
        void keyPressed(int key) {
            
            if (key == 'u') doSave = !doSave;
            unsigned idx = key - '0';
            if (idx < 5) {
                if (doSave) {
                    presets->savePreset(idx);
                } else {
                    //presets->loadPreset(idx);
                    presets->animatePreset(idx);
                }
            }
        }
        
    };
}
