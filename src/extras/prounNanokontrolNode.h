#pragma once

#include "prounNode.h"
#include "NanoKontrol2.h"

namespace proun {
    template <typename T>
    class NanokontrolNode : public Node
    {
    public:
        
        NanoKontrol2 *nanokontrol;
        ofPtr<ofParameter<T>> value;
        
        NanokontrolNode(T val):Node("nanokontrol")
        {
            value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));
            nanokontrol = new NanoKontrol2();
            nanokontrol->setup();
            
            for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                output.add("value" + ofToString(i));
                float v = 0.0;
                ofPtr<ofAbstractParameter> ptr = ofPtr<ofAbstractParameter>(new ofParameter<float>(v));
                output.setValue("value" + ofToString(i), ptr);
            }
            
            
            ofSetLogLevel("NanoKontrol2", OF_LOG_SILENT);
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {
//            
            for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                string name = "value" + ofToString(i);
                float value = 0;
                if (i < 8) {
                    value = nanokontrol->channel[i].knob;
                } else {
                    value = nanokontrol->channel[i - 8].slider;
                }
                ofAbstractParameter *iabstract = output.getValue(name).get();
                if(ofParameter<float> *v = dynamic_cast<ofParameter<float>*>(iabstract)) {
                    v->set(v->getMin() + value * v->getMax());
                }
            }
            
            output.setValue("value", value);
        }
        
        virtual void contentDraw ()
        {
            this->height = 18 * 10 + 1;
            
            Node::contentDraw();
            
            ofPushView();
            ofPushMatrix();
            ofPushStyle();
            ofTranslate(55, 3);
            
            int size = 10;
            int sizeX = 65;
            ofSetLineWidth(1);
            
            for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                float value = 0;
                if (i < 8) {
                     value = nanokontrol->channel[i].knob;
                } else {
                     value = nanokontrol->channel[i - 8].slider;
                }
                ofFill(); ofDrawRectangle(-sizeX + size, i * (size), 1.0 * value * sizeX, size);
                ofNoFill(); ofDrawRectangle(-sizeX + size, i * (size), sizeX, size);
            }
            ofFill();
            
            ofPopStyle();
            ofPopMatrix();
            ofPopView();
            
            ofFill();
        }
        
        virtual string customSerialize() {
            stringstream serialized;
            for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                string name = "value" + ofToString(i);
                ofAbstractParameter *iabstract = output.getValue(name).get();
                if(ofParameter<float> *v = dynamic_cast<ofParameter<float>*>(iabstract)) {
                    serialized << ofToString(v->get()) << "|";
                }
            }
            return serialized.str() + ";";
        }
        
        virtual void customDeSerialize(string serialized) {
            vector<string> tstrings = ofSplitString(serialized, "|");
            for (int i = 0; i < tstrings.size(); i++) {
                string name = "value" + ofToString(i);
                float value = ofToFloat(tstrings[i]);
                ofAbstractParameter *iabstract = output.getValue(name).get();
                if(ofParameter<float> *v = dynamic_cast<ofParameter<float>*>(iabstract)) {
                    v->set(value);
                }
                
                if (i < 8) {
                    nanokontrol->channel[i].knob = value;
                } else {
                    nanokontrol->channel[i - 8].slider = value;
                }
            }
        }

    };
}
