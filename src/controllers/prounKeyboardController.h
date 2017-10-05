#pragma once
#include "prounController.h"
#include "prounModel.h"

namespace proun {
    
    class EmptyKeyboardController
    {
    protected:
        Controller *controller;
        Model *model;        
    public:
        bool isShift = false;
        void enable();
        void disable();

        void setup(Controller *controller, Model *model);
        virtual void keyPressed(ofKeyEventArgs &e);
        void keyReleased(ofKeyEventArgs &e);
    };
    
    class BaseKeyboardController : public EmptyKeyboardController
    {
    public:
        virtual void keyPressed(ofKeyEventArgs &e);
    };
    
    class KeyboardController : public BaseKeyboardController
    {
    private:
        typedef BaseKeyboardController super;
    public:
        virtual void keyPressed(ofKeyEventArgs &e);
    private:
        void createByNumber(int number);
    };
}
