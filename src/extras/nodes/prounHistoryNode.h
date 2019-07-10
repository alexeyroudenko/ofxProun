#pragma once

#include "prounNode.h"
#include "ofxHistoryPlot.h"

namespace proun {
    template <typename T>
    class HistoryNode : public Node
    {
    public:
        
        ofPtr<ofParameter<T>> value;
        
        HistoryNode(T val):Node("history")
        {
            value = ofPtr<ofParameter<T> >(new ofParameter<T>(val));

            _history = new ofxHistoryPlot(NULL, "history", 100, false);
            _history->setColor(ofColor(255));
            _history->setShowNumericalInfo(false);
            _history->setDrawTitle(false);
            _history->setGridColor(ofColor(32));
            _history->update(0);
            
            input.add("value");
            output.add("value");
        }
        
        virtual bool validate()
        {
            return input.doesAllValuesExist();
        }
        
        virtual void evaluate()
        {
            float v = input.getValue<float>("value");
            _history->update(v);
            
            //T r = getInputValue<T>("value");
            //setOutputValue("value", value);
            
            this->value->set(v);
            output.setValue("value", value);
        }
        
        virtual void contentDraw ()
        {
            this->width = 100;
            this->height = 40 + 1;
            
            Node::contentDraw();
            
            ofPushStyle();
            ofDisableBlendMode();
            ofSetColor(155);
            _history->draw(10, -8, this->width - 25, this->height - 2);
            ofPopStyle();
            ofFill();
        }
        
    protected:
        ofxHistoryPlot *_history;

    };
}
