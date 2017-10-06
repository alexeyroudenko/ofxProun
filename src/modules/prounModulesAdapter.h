#pragma once

#include "prounModule.h"

namespace proun {
    
    class ModulesAdapter
    {
        
        Module *empty;
        int current = 0;
        
    public:
        
        ModulesAdapter() {
            empty = new Module();
        }
        
        void setup() {
        }
        
        void add(Module *module) {
            modules.push_back(module);
        }
        
        bool doPresets() {
            return getState()->doPresets();
        }
        
        void update() {
            getState()->update();
        }
        
        void draw() {
            getState()->draw();
        }
        
        Module *getState() {
            if (modules.size() ==  0) return empty;
            return modules.at(current);
        }
        
        string getInfo() {
            return getState()->getInfo();
        }
        
        void keyPressed(ofKeyEventArgs &e) {
            if (modules.size() ==  0) return;
            if (e.key == ' ') {
                current++;
                current = current % modules.size();
            }
            
            getState()->keyPressed(e.key);
        }
        
        void keyReleased(ofKeyEventArgs &e) {
            
        }
        
    protected:
        
        vector<Module*> modules;
        
    };
}
