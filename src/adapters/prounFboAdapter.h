#pragma once

#include "ofMain.h"
#include "prounModel.h"
#include "prounFboNode.h"
#include "prounSettings.h"

namespace proun {
    class FboAdapter {
    protected:
        Model *model;
        map<string, ofFbo*>  fbos;
        vector<FboNode*>nodeContainers;
        
    public:
        ofParameter<bool> doGui;
        
        void setup(Model *model_) {
            model = model_;
        }
        
        void addNode(FboNode *node) {
            string name = node->settings->getName();
            ofLogVerbose("prounGuiAdapter", "added: " + name);
            nodeContainers.push_back(node);
            fbos[name] = &node->fbo;
        }
        
        void update() {
            for (auto node:nodeContainers) {
                node->update();
            }
        }
        
        void draw() {
            
            if (Settings::getInstance().doDrawNodes) {
                vector<proun::NodePtr>nodes = model->nodes;
                for (auto node:nodes) {
                    string name = node->getName();
                    if (fbos[name]) {
                        ofPushMatrix();
                        ofTranslate(node->getX(), node->getY());
                        if (Settings::getInstance().fboAtTop == false) {
                            ofTranslate(0, node->getHeight() + 5);
                        }
                        
                        float aspect = fbos[name]->getHeight() / fbos[name]->getWidth();
                        aspect = 9.0 / 16.0;
                        
                        ofPushStyle();
                        ofDisableBlendMode();
                        ofDisableAlphaBlending();
                        ofBlendMode(OF_BLENDMODE_MULTIPLY);
                        ofSetLineWidth(1);
                        ofRectangle rect2(0, 0, 512 * 0.25, 512 * aspect * 0.25);
                        
                        ofSetColor(128, 255);
                        ofFill();
                        ofDrawRectangle(rect2);
                        
                        ofSetColor(255, 255);
                        ofNoFill();
                        ofDrawRectangle(rect2);
                        ofFill();
                        ofPopStyle();
                        
                        ofPushMatrix();
                        ofRectangle rect(0, 0, 512, 512 * aspect);
                        ofScale(0.25, 0.25);
                        ofSetColor(255);
                        ofFill();
                        fbos[name]->draw(rect);
                        ofFill();
                        ofPopMatrix();
                        
                        ofPopMatrix();
                    }
                }
            }
        }
    };
}
