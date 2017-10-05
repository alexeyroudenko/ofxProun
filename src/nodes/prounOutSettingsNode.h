#pragma once
#include "prounNode.h"

namespace proun {
    
    typedef ofPtr<ofParameter<float>> ofParameterPtr;
    
    template <typename T>
    class OutSettingsNode : public Node
    {
    public:
        
        ofPtr<ofParameterGroup> value;
        ofPtr<ofAbstractParameter> valueptr;
        
        ~OutSettingsNode() {
            ofLogVerbose("OutSettingsNode", "destructor");
            value = NULL;
        }
        
        OutSettingsNode(string name, ofPtr<ofParameterGroup> val):Node(name) {
            name = val->getName();
            value = val;
            
            for(std::size_t i = 0; i < value.get()->size(); i++){
                string type = value.get()->getType(i);
                ofParameter<float> parameter = value.get()->getFloat(i);
                output.add(parameter.getName().c_str());
            }
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            for(std::size_t i = 0; i < value.get()->size(); i++){
                string type = value.get()->getType(i);
                ofParameter<float> parameter = value.get()->getFloat(i);
                output.setValue(parameter.getName().c_str(), ofPtr<ofAbstractParameter>(new ofParameter<float>(parameter.get())));
            }
        }
        
        virtual void contentDraw ()
        {
            this->width = 90;
            this->width = 120;
            this->height = value.get()->size() * 10 + 25;
            
            Node::contentDraw();
            
            ofSetColor(150);
            for(std::size_t i = 0; i < value.get()->size(); i++){
                auto p = value.get()->getFloat(i);
                proun::Style::font.get()->drawString(value.get()->getName(i) + " " + ofToString(p), 12, 13 + i * 10);
            }
        }
        
    private:
    };
}
