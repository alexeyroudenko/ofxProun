#pragma once
#include "prounUtils.h"
#include "prounStyle.h"
#include "prounNode.h"
#include "prounModel.h"
#include "prounController.h"
#include "prounMouseController.h"
#include "prounKeyboardController.h"
#include "prounFboAdapter.h"
#include "prounGuiAdapter.h"

#include "prounModule.h"
#include "prounPatchingModule.h"
//#include "prounPresetsModule.h"

namespace proun {
    
    class App
    {
        
    private:
        
    protected:
        
        MouseController mouseController;
        EmptyKeyboardController *keyboardController;
        
        GuiAdapter guiAdapter;
        FboAdapter fboAdapter;
        
        Module *getState();
        
        void onSelect(proun::Model::prounEventArgs &e);
        void onChangeModel(proun::Model &model);
        
    public:
        
        App();
        ~App();
        
        Model *model;
        Controller *controller;
        
        void setup(string fileName);
        void initModules();
        void update();
        void draw();
        
        void load();
        void save();
        
        //void addModule(Module *module);
        void addNode(ofParameterGroup *settings,  bool isOutput = false);
        void addNode(FboNode *node,  bool isOutput = false);
        
        void drawBackground();
        void drawInfo(string externalString = "", bool append = true);
        
        void ckeckLocalConfig();
        void enableButtons();
        void disableButtons();
        void disableMouse();
        void enableMouse();
        void disableAllButtons();
    };
}
