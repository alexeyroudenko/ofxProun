#pragma once

#include "prounNode.h"

namespace proun {
    class FboNode
    {
    public:
        FboNode(){
            this->settings = new ofParameterGroup();
        };
        ofParameterGroup *settings;
        ofFbo fbo;
        bool created;
      
        virtual void setup(){};
        virtual void update(){};
        virtual void draw(){};
    };
}
