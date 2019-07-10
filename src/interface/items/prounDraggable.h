#pragma once
#include "ofMain.h"
#include "prounStyle.h"

namespace proun {
    
    class Draggable : public ofRectangle
    {
    public:
        
        Draggable() {}
        
        ~Draggable() {
            ofLogVerbose("ofxDraggable", "destructor");
        }
        
        ofEvent<bool> onSelect;
        
        void draw();
        
        void setHover(bool value);
        bool isHover();
        
        void setSelected(bool value);
        bool isSelected();
        
        void setDragging(bool value, int x = -1, int y = -1);
        bool isDragging();
        
        void drag(int x, int y);
        void addDrag(int dx, int dy);
        
        
        string debugString();
        
    private:
        
        bool hover;
        bool selected;
        bool dragging;
        void moveToNet();
        
        ofVec2f pressedPosition;
    };
};
