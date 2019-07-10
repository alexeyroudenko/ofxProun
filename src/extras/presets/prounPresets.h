#pragma once

#include "ofMain.h"
#include "prounPresetsController.h"

using namespace proun;

namespace ofxPresets {
    
    class Model {
        int current;
        string folder = "";
        string name = "";
        ofDirectory dir;
        string lastLoaded = "";
        
        float controls[16];
        bool isInterpolate = true;
        
    public:
        ofParameterGroup *settings;
        ofParameter<bool> interpolate;
        ofParameter<float> interp;
        
        ofParameter<bool> doswitch;
        ofParameter<int> autoswitch;
        
        ofEvent<string> onSelect;
        
        void setup(string folder_, string name_ = "") {
            
            settings = new ofParameterGroup();
            settings->setName("presets");
            settings->add(interpolate.set("interpolate", true));
            settings->add(interp.set("interp", 0.5,0,1));
            settings->add(doswitch.set("doswitch", true));
            settings->add(autoswitch.set("autoswitch", 2.,2.,1024));

            
            interp = 0.2;
            interpolate = true;
            name = name_;
            folder = folder_;
            current = 0;
        }
        
        void update() {
            float summDelta = 0;
            if (doswitch) {
                if (ofGetFrameNum() % autoswitch == 0) {
                    loadNext();
                }
            }
            if (isInterpolate) {
                for (int i = 0; i < 16; i++) {
                    float delta = abs(controls[i] - PresetParameters::getInstance().controls[i]);
                    summDelta += delta;
                    PresetParameters::getInstance().controls[i] = (controls[i] * (1.0 - interp) + PresetParameters::getInstance().controls[i] * interp);
                    PresetParameters::getInstance().dirty = true;
                }
                
                //ofLogVerbose("ofxmodel", "interpolating " + ofToString(summDelta));
                if (summDelta < 0.01) {
                    isInterpolate = false;
                    //ofLogVerbose("ofxmodel", "interpolating done");
                }
            }
        }
        
        void startInterpolate(string fileName) {
            int i = 0;
            ofBuffer buffer = ofBufferFromFile(ofToDataPath(fileName));
            if(buffer.size()) {
                for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
                    string line = *it;
                    if(line.empty() == false) {
                        float v = ofToFloat(line);
                        controls[i] = v;
                        i++;
                    }
                }
            }
            isInterpolate = true;
        }
        
        void loadNext() {
            string directory = folder;
            dir.listDir(directory);
            dir.sort();
            
            current++;
            if (dir.size() <= current) current = 0;
            
            string fileName = dir.getPath(current);
            ofFile file(fileName);
            lastLoaded = fileName;
            startInterpolate(lastLoaded);
            ofNotifyEvent(onSelect, fileName);
        }
        
        void loadPrevious() {
            string directory = folder;
            dir.listDir(directory);
            dir.sort();
            
            current--;
            if (current < 0) current = dir.size() - 1;
            
            string fileName = dir.getPath(current);
            ofFile file(fileName);
            lastLoaded = fileName;
            ofNotifyEvent(onSelect, fileName);
        }
        
        void loadAt(int i) {
            ofLogVerbose("ofxmodel", "loadAt " + ofToString(i));
            string directory = folder;
            dir.listDir(directory);
            dir.sort();
            current = i;
            
            string fileName = dir.getPath(i);
            lastLoaded = fileName;
            ofNotifyEvent(onSelect, fileName);
        }
        
        string getCurrentName() {
            return lastLoaded;
        }

        int getCurrent() {
            return current;
        }
        
        int getCount() {
            string directory = folder;
            dir.listDir(directory);
            dir.sort();
            return dir.size();
        }
        

        string getFolderName() {
            return folder;
        }
        
    };
}

