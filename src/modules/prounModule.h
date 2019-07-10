#pragma once

#include "prounModel.h"

namespace proun {
    
    class Module
    {
        
    protected:
    
    public:
        
        virtual bool doPresets() {
			return false;
        };
        
        virtual void setup(){
        };
        
        virtual void update(){
        };
        
        virtual void draw(){
        };
        
		virtual string getInfo() { return ""; };
        
        virtual void keyPressed(int key) {};
    };
}
