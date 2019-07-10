#pragma once
#include "prounNode.h"

namespace proun {
    
    template <typename T>
    class ValueNode : public Node
    {
    public:
        ofPtr<ofParameter<T> > value;
        
        ValueNode(string name, T val):Node(name) {
            value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
            output.add("value");
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            output.setValue("value", value);
        }
        
        virtual void contentDraw () {
            Node::contentDraw();
            
            stringstream info;
            info << name + "::" + value->toString() + "\n";
            proun::Style::font.get()->drawString(info.str(), 0, 0);
        }
        
        virtual string customSerialize() {
            return value->toString() + ";";
        }
        
        virtual void customDeSerialize(string serialized) {
            ofParameter<float>fv = *value.get();
            fv = ofToFloat(serialized) + fv.get();
        }
        
        virtual void keyPressed(int key) {
            ofLogVerbose("ValueNode", ofToString(key));
            float inc = 0;
            if (key == '+') inc = .1;
            if (key == '-') inc = -.1;
            if (key == '=') inc = 1;
            if (key == '-') inc = -1;
            ofParameter<float>fv = *value.get();
            fv = inc + fv.get();
        }

    };
}
