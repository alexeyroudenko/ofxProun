#pragma once
#include "ofMain.h"

namespace proun {
    class Settings
    {
    public:
        ofParameterGroup *settings;
        ofParameter<bool> doCreations = true;
        ofParameter<bool> doSelections = true;
        ofParameter<bool> doDrawNodes = false;
        ofParameter<bool> doDrawFbo = true;
        ofParameter<bool> showGUIS = false;        
        ofParameter<bool> doMoves = true;
        ofParameter<bool> needSave = false;
        ofParameter<bool> fboAtTop = false;
        ofParameter<int> bg = -1;
        //ofParameter<int> info = 0;
       
        static Settings& getInstance() {
            static Settings INSTANCE;
            return INSTANCE;
        }
        
        void keyPressed(int key)
        {
            //if (key == 'i') {info++;info = info % 2;};
            //if (key == ' ') {info++;info = info % 2;};
            if (key == 't') fboAtTop = !fboAtTop;
            if (key == 'g') showGUIS = !showGUIS;
            if (key == 'm') doMoves = !doMoves;
            if (key == 'b') {bg++; bg = bg % 3;};
            if (key == OF_KEY_TAB) doDrawNodes = !doDrawNodes;
            if (key == 147) doDrawNodes = !doDrawNodes;
            if (key == 63251) doDrawNodes = !doDrawNodes;
        }
        
    private:
        
        Settings(){
            settings = new ofParameterGroup();
            settings->setName("proun");
            settings->add(doCreations.set("doCreations", true));
            settings->add(doSelections.set("doSelections", true));
            settings->add(doDrawNodes.set("doDrawNodes", true));
            settings->add(doDrawFbo.set("doDrawFbo", true));
            settings->add(showGUIS.set("showGUIS", false));
            settings->add(doMoves.set("doMoves", true));
            settings->add(fboAtTop.set("fboAtTop", true));
            settings->add(bg.set("bg", 1,0,2));
            //settings->add(info.set("info", 1,0,2));
            
            proun::Style::loadFont("fonts/iflash-502.ttf", 6);
            proun::Style::loadBigFont("fonts/iflash-705.ttf", 6);
        };
    };
}

