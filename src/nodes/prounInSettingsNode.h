#pragma once
#include "prounNode.h"

namespace proun {
    
    typedef ofPtr<ofParameter<float>> ofParameterPtr;
    
    template <typename T>
    class InSettingsNode : public Node
    {
    public:
        
        ofPtr<ofParameterGroup> value;
        vector<ofPtr<ofAbstractParameter> > values;
        ofPtr<ofAbstractParameter> valueptr;
        
        ~InSettingsNode() {
            ofLogVerbose("InSettingsNode", "destructor");
            value = NULL;
        }
        
        InSettingsNode(string name, ofPtr<ofParameterGroup> val):Node(name) {
            value = val;
            
            for(std::size_t i = 0; i < value.get()->size(); i++){
                string type = value.get()->getType(i);
                ofParameter<float> parameter = value.get()->getFloat(i);
                input.add(parameter.getName().c_str());
                ofLogVerbose("InSettingsNode", "%s", parameter.getName().c_str());
            }
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
            int k = 0;
            for (vector<string>::iterator i = input.names.begin(); i != input.names.end(); i++) {
				std::map<string, ofPtr<ofAbstractParameter> >::iterator val = input.values.find(*i);
                if (val != input.values.end()) {
                    ofPtr<ofAbstractParameter> iptr = val->second;
                    string name = val->first;
                    ofAbstractParameter *iabstract = iptr.get();
                    if(ofParameter<float> v = *dynamic_cast<ofParameter<float>*>(iabstract)) {
                        for(std::size_t i = 0; i < value.get()->size(); i++){
                            
                            auto p = value.get()->getFloat(i);
                            string name2 = p.getName();
                            if (strcmp(name2.c_str(), name.c_str()) == 0) {
                                p.set(v.get());
                            }
                            
                        }
                    }
                }
                k++;
            }
        }
        
        virtual void contentDraw ()
        {
            
            this->width = 128;//maxLetters * proun::Style::font.get()->getGlyphBBox().width + 10;
            this->height = value.get()->size() * 10 + 15;
            Node::contentDraw();
            stringstream info;
            ofSetColor(proun::Style::textColor);
            for(std::size_t i = 0; i < value.get()->size(); i++){
                auto p = value.get()->getFloat(i);
                string line = value.get()->getName(i) + " " + ofToString(p);
                if (line.length() > proun::Style::maxCharachters) line = line.substr(0, proun::Style::maxCharachters);
                info << line << endl;
            }
            proun::Style::font.get()->setLineHeight(10);
            proun::Style::font.get()->drawString(info.str(), Style::textPaddingX, 10 + 0 * 10);
        }
        
    private:
        int maxLetters = 0;
    };
}
