#pragma once
#include "prounNode.h"

namespace proun {
    
    class AddNode : public Node
    {
    public:
        
        AddNode(string name):Node(name) {
            input.add("value1");
            input.add("value2");
            output.add("result");
        }
        
        virtual bool validate()
        {
            return input.doesAllValuesExist();
        }
        
        virtual void evaluate()
        {
            if (validate()) {
                float v1 = input.getValue<float>("value1");
                float v2 = input.getValue<float>("value2");
                output.setValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(v1 + v2)));
            } else {
                output.setValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(0)));
            }
        }
        
        virtual void contentDraw () {
            this->height = 2 * 10 + 15;
            
            stringstream info;
            info << name + "::";
            if (validate()) {                
                info << output.getValue("result")->toString() << endl;
            }
            proun::Style::font.get()->drawString(info.str(), 0, 0);
        }
    };
}
