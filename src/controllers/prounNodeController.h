#pragma once
#include "ofMain.h"

namespace proun {
    
    class prounNodeController {
    public:
        vector<ofPtr<ofParameter<float>>> values;
        int selectedIndex;
        
        prounNodeController():selectedIndex(-1) {
            
        }

        virtual void keyPressed(int key)
        {
            if (key == ' ') {
                selectedIndex++;
                selectedIndex = selectedIndex % values.size();
            }
            
            float inc = 0;
            
            if (key == '_') inc = -.01;
            if (key == '=') inc = .01;
            
            if (key == '-') inc = -.1;
            if (key == '+') inc = .1;
            
            if (key == 356) inc = -1.0;
            if (key == 358) inc = 1.0;

            if (key == 359) inc = -10.0;
            if (key == 357) inc = 10.0;
            
            if (selectedIndex >= 0) {
                ofPtr<ofParameter<float>> p = values[selectedIndex];
                ofParameter<float>*pp = p.get();
                float v = inc + pp->get();
                pp->set(v);
            }
        }
    };
}
