#pragma once
#include "prounValueable.h"
#include "prounSerializable.h"

namespace proun {
    
    class Node : public Serializable
    {
    protected:
        bool patching = false;
    public:
        
        Node(string name_);
        ~Node();
        virtual void evaluate();
        
        void setPatching(bool value);
        
        void draw();
        void drawInputs(Connectable *node);
        virtual void contentDraw();

        string infoString();
        
        virtual void keyPressed(int key);
    };
    
    typedef ofPtr<Node> NodePtr;
}
