#pragma once

#include "prounModel.h"

namespace proun {
    
    class Module
    {
        
    protected:
    
    public:
        
        virtual bool doPresets() {
        };
        
        virtual void setup(){
        };
        
        virtual void update(){
        };
        
        virtual void draw(){
        };
        
        virtual string getInfo() {};
        
        virtual void keyPressed(int key) {};
    };
}
