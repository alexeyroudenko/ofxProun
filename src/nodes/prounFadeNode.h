#pragma once
#include "prounNode.h"

namespace proun {
    
    template <typename T>
    class FadeNode : public Node
    {
    public:
        ofPtr<ofParameter<T>> value;
        ofPtr<ofParameter<T>> result;
        
        FadeNode(string name, T val):Node(name) {
            this->value = ofPtr<ofParameter<float>>(new ofParameter<float>(val));
            this->result = ofPtr<ofParameter<float>>(new ofParameter<float>(0.0));
            input.add("value");
            output.add("result");
            output.setValue("result", value);
        }
        
        virtual bool validate()
        {
            return input.doesAllValuesExist();
        }
        
        virtual void evaluate()
        {
            if (validate()) {
                float targetV = input.getValue<float>("value");
                float currentV = result->get();
                float fadeValue = 0.05;
                if (currentV > targetV) {
                    currentV = (1.0 - fadeValue) * currentV + fadeValue * targetV;
                } else {
                    currentV = targetV;
                }
                this->result.get()->set(currentV);
            } else {
                this->result.get()->set(0.5);
            }
            
            output.setValue("result", result);
        }
        
        virtual void contentDraw () {
            Node::contentDraw();
            height = 25;
            stringstream info;
            info << name + "::" + result->toString() + "\n";
            proun::Style::font.get()->drawString(info.str(), 0, 0);
        }
        
        virtual string customSerialize() {
            return value->toString() + ";";
        }
        
        virtual void customDeSerialize(string serialized) {
            ofParameter<float>fv = *value.get();
            fv = ofToFloat(serialized) + fv.get();
        }
    };
}
