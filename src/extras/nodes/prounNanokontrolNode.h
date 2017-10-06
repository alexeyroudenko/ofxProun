#pragma once

#include "prounNode.h"
#include "NanoKontrol2.h"

namespace proun {
    
    class PresetParameters {
        
    public:
        bool dirty;
//        ofParameterGroup *values;
//        vector<ofParameter<float>> parameters;
        float controls[16];
        
        static PresetParameters& getInstance() {
            static PresetParameters INSTANCE;
            return INSTANCE;
        }
        
        void addValue(ofParameter<float> parameter) {
            //values->add(parameter);
            //parameters.push_back(parameter);
        }
        
        void load(string fileName) {
            ofLogVerbose("PresetParameters", "loadFromFile: fileName:" + fileName);
            int i = 0;
            ofBuffer buffer = ofBufferFromFile(ofToDataPath(fileName));
            if(buffer.size()) {
                for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
                    string line = *it;
                    if(line.empty() == false) {
                        //ofLogVerbose("PresetParameters", "line:" + line);
                        float fline = ofToFloat(line);
                        controls[i] = fline;
                        //ofLogVerbose("PresetParameters", "controls[i]:" + ofToString(controls[i]));
                        i++;
                    }
                    //cout << line << endl;
                }
            }
            dirty = true;
        }
        
        void save(string fileName) {
            ofLogVerbose("PresetParameters", "saveState: fileName:" + fileName);
            ofFile file(ofToDataPath(fileName), ofFile::WriteOnly);
            for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                file << ofToString(controls[i]) << endl;
            }
            file.close();
        }

        
    private:
        PresetParameters() {
            //values = new ofParameterGroup();
        };
    };
    
    
    
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
                ofParameter<float> *parameter = new ofParameter<float>(v);
                ofPtr<ofAbstractParameter> ptr = ofPtr<ofAbstractParameter>(parameter);
                output.setValue("value" + ofToString(i), ptr);
                PresetParameters::getInstance().addValue(*parameter);
            }
            
            PresetParameters::getInstance().dirty = false;
            ofSetLogLevel("NanoKontrol2", OF_LOG_SILENT);
        }
        
        virtual bool validate()
        {
            return true;
        }
        
        virtual void evaluate()
        {

            
            if (PresetParameters::getInstance().dirty) {
                //ofLogVerbose("PresetParameters", "need update");
                for (int i = 0; i < NanoKontrol2::MixerChannels * 2; i++) {
                    float value = PresetParameters::getInstance().controls[i];
                    if (i < 8) {
                        nanokontrol->channel[i].knob = value;
                    } else {
                        nanokontrol->channel[i - 8].slider = value;
                    }
                }
                PresetParameters::getInstance().dirty = false;
                //ofLogVerbose("PresetParameters", "updated");
            }
            
            
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
                    PresetParameters::getInstance().controls[i] = value;
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
