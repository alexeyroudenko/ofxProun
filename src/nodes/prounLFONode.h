#pragma once
#include "prounNode.h"

namespace proun {
    
    template <typename T>
    class LFONode : public Node
    {
    public:
        ofPtr<ofParameter<T>> frequency;
        ofPtr<ofParameter<T>> result;
        
        LFONode(string name, T val):Node(name) {
            this->frequency = ofPtr<ofParameter<T>>(new ofParameter<float>(val));
            this->result = ofPtr<ofParameter<T>>(new ofParameter<float>(0.0));
            input.add("frequency");
            output.add("result");
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            float fr = frequency->get();
            if (inputs.size() > 0) {
                fr = (input.getValue<float>("frequency"));
            } else {
                fr = frequency->get();
            }
            this->result.get()->set(sin(ofGetElapsedTimef() * fr));
            output.setValue("result", result);
        }
        
        virtual void contentDraw () {
            
            Node::contentDraw();
            
            stringstream info;
            info << name + "::" + result->toString() + "\n";
            info << "     " << frequency->toString() << "\n";
            proun::Style::font.get()->drawString(info.str(), 0, 0);
        }
        
        virtual string customSerialize() {
            return frequency->toString() + ";";
        }
        
        virtual void customDeSerialize(string serialized) {
            ofParameter<float>fv = *frequency.get();
            fv = ofToFloat(serialized) + fv.get();
        }
        
        void keyPressed(int key) {
            float inc = 0;
            if (key == '+') inc = .1;
            if (key == '-') inc = -.1;
            if (key == '=') inc = .01;
            if (key == '-') inc = -.01;
            float cur = frequency->get();
            frequency->set(inc + cur);
        }
    };
}
