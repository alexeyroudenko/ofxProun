#pragma once

#include "ofMain.h"
#include "prounPresets.h"

namespace ofxPresets {
    
    class Controller {
        
    public:
        
        ofxPresets::Model *model;
        
        Controller() {
            model = new Model();
            model->setup("presets", "presets.cfg");
        }
        
        void setup() {
            //ofAddListener(model->onSelect, this, &Controller::onSelectPreset);
        }
        
        
        /* --------------------------------------------------------------
         # commands
         #
         #
         #
         # -------------------------------------------------------------- */
        void saveCurrent() {
            ofLogVerbose("ofxPresets", "saveCurrent " + model->getCurrentName());
            PresetParameters::getInstance().save(model->getCurrentName());
        }
        
        void savePreset() {
            string folder =  model->getFolderName();
            string file = folder + "" + getDateString() + ".txt";
            ofLogVerbose("ofxPresets", "savePreset " + file);
            proun::PresetParameters::getInstance().save(file);
        }

        void savePreset(int inx) {
            string folder = model->getFolderName();
            string file = folder + ofToString(inx) + ".txt";
            ofLogVerbose("ofxPresets", "savePreset:" + file);
            proun::PresetParameters::getInstance().save(file);
        }
        
        void loadPreset(int ifx) {
            string folder =  model->getFolderName();
            string file = folder + ofToString(ifx) + ".txt";
            ofLogVerbose("ofxPresets", "loadPreset:" + file);
            proun::PresetParameters::getInstance().load(file);
        }
        
        void animatePreset(int ifx) {
            string folder =  model->getFolderName();
            string file = folder + ofToString(ifx) + ".txt";
            ofLogVerbose("ofxPresets", "animatePreset:" + file);
            if (model->interpolate) {
                model->startInterpolate(file);
            }
        }
        
        void onSelectPreset(string &fileName) {
            ofLogVerbose("ofxPresets", "onSelectPreset " + fileName);
            if (model->interpolate) {
                model->startInterpolate(fileName);
            }
        }
            

        
    protected:
        string formatInt(int number) {
            if (number < 10) return "0" + ofToString(number);
            return ofToString(number);
        }
        
        string getDateString() {
            string fileName = ofToString(ofGetYear()) + "-" +
            formatInt(ofGetMonth()) + "-" +
            formatInt(ofGetDay()) + "_" +
            formatInt(ofGetHours()) + "-" +
            formatInt(ofGetMinutes()) + "-" +
            formatInt(ofGetSeconds());
            return fileName;
        }

    };
}

