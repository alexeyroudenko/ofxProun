#pragma once
#include "prounStyle.h"
#include "prounValueable.h"
#include "prounNode.h"
#include "prounFactory.h"

namespace proun {
    
    class Model
    {
        
    public:
        
        Model() {}
        vector<NodePtr>nodes;
        
        Factory *factory;
        
        string fileName = "proun.csv";
        
        class prounEventArgs : public ofEventArgs
        {
        public:
            proun::Node *node;
            string paramName;
        };
        ofEvent<prounEventArgs> selectEvent;
        ofEvent<prounEventArgs> deSelectEvent;
        ofEvent<prounEventArgs> moveEvent;
        ofEvent<string> onLoad;
        ofEvent<Model*> onChange;
        
        void add(NodePtr nodePtr);
        NodePtr getById(int uid);
        NodePtr getByName(string name);
        
        void update();
        void draw();
        
        bool hasNode(int uid);
        bool hasNode(string name);
        
        bool hasNodeAt(int x, int y);
        int getCountSelected();
        Node *lastSelected;
        
        void updateValuables();
        void evaluateInputs(Connectable *node);
        void connect(Connectable::Connection o, Connectable::Connection i) {
            ofLogVerbose("Model", "connect:" + o.paramName + "@" + o.node->getName() + "---" + i.paramName + "@" + i.node->getName());
            o.node->outputs.insert(pair<string, Connectable::Connection>(i.paramName, o));
            i.node->inputs[i.paramName] = o;
        };
    };
}
