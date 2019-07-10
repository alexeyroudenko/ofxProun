#pragma once
#include "prounNode.h"

namespace proun {
    
    template <typename T>
    class TimeNode : public Node
    {
    public:
        ofPtr<ofParameter<T> > value;
        
        TimeNode(string name, T val):Node(name) {
            value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
            output.add("value");
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            this->value->set(ofGetElapsedTimef());
            output.setValue("value", value);
        }
        
        virtual void contentDraw () {
            
            Node::contentDraw();
            
            stringstream info;
            info << name + "::" + ofToString(value->toString(), 2) + "\n";
            //info << Draggable::debugString() << "\n";
            proun::Style::font.get()->drawString(info.str(), 0, 0);
        }
    };
}
