#pragma once
#include "prounNode.h"

namespace proun {
    
    class MultiplyNode : public Node
    {
    public:
        
        MultiplyNode(string name):Node(name) {
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
                output.setValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(v1 * v2)));
            } else {
                output.setValue("result", ofPtr<ofAbstractParameter>(new ofParameter<float>(0)));
            }
        }
        
        virtual void contentDraw () {
            stringstream info;
            info << name + "::";
            if (validate()) {                
                info << output.getValue("result")->toString() << endl;
            }
            string s = info.str();
            if (s.length() > proun::Style::maxCharachters) s = s.substr(0, proun::Style::maxCharachters);
            proun::Style::font.get()->drawString(s, 0, 0);
        }
    };
}
