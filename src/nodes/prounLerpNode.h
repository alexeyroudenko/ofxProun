#pragma once
#include "prounNode.h"
#include "prounNodeController.h"

namespace proun {
    
    template <typename T>
    class LerpNode : public Node, public prounNodeController
    {
    public:
        ofPtr<ofParameter<T>> value;
        ofPtr<ofParameter<T>> min;
        ofPtr<ofParameter<T>> max;
        ofPtr<ofParameter<T>> result;
        
        LerpNode(string name):Node(name) {
            this->value = ofPtr<ofParameter<T>>(new ofParameter<float>(0.0));
            this->min = ofPtr<ofParameter<T>>(new ofParameter<float>(0.0));
            this->max = ofPtr<ofParameter<T>>(new ofParameter<float>(512.0));
            this->result = ofPtr<ofParameter<T>>(new ofParameter<float>(0.0));
            
            input.add("value");
            input.add("min");
            input.add("max");
            
            output.add("result");
            output.setValue("result", ofPtr<ofAbstractParameter>(this->result));
            
            walkValues.push_back(this->min);
            walkValues.push_back(this->max);
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            
            float v = this->value->get();
            float vmin = this->min->get();
            float vmax = this->max->get();
            
            if (input.values.find("value") != input.values.end()) {
                v = input.getValue<float>("value");
            }

            if (input.values.find("min") != input.values.end()) {
                vmin = input.getValue<float>("min");
            }
            
            if (input.values.find("max") != input.values.end()) {
                vmax = input.getValue<float>("max");
            }
            
            this->result.get()->set(vmin + abs(v * (vmax - vmin)));
            output.setValue("result", this->result);
        }
        
        /* --------------------------------------------------------------
         #
         #
         #
         #
         # -------------------------------------------------------------- */
        virtual string customSerialize() {
            return value->toString() + ", " + this->min->toString() + "," + this->max->toString();
        }
        
        virtual void customDeSerialize(string serialized) {
            vector<string> tstrings = ofSplitString(serialized, ",");
            this->value->set(ofToFloat(tstrings[0]));
            this->min->set(ofToFloat(tstrings[1]));
            this->max->set(ofToFloat(tstrings[2]));
        }
        
        
        /* --------------------------------------------------------------
         #
         #
         #
         #
         # -------------------------------------------------------------- */
        virtual void contentDraw () {
            this->height = 44;
            
            ofPushStyle();
            stringstream info;
            info << name + "::";
            if (validate()) {
                info << output.getValue("result")->toString() << endl;
                stringstream details;
                details << (selectedIndex == 0 ? ">" : "") << ofToString(this->min->get()) << endl;
                details << (selectedIndex == 1 ? ">" : "") << ofToString(this->max->get()) << endl;
                ofSetColor(Style::textColor);
                proun::Style::font.get()->drawString(details.str(), Style::textPaddingX, 20);
            }
            ofSetColor(Style::titleColor);
            proun::Style::font.get()->drawString(info.str(), 0, 0);
            ofPopStyle();
        }
        
        virtual void keyPressed(int key) {
            prounNodeController::keyPressed(key);
        }
    };
}
