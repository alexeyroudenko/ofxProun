#include "ofxProun.h"
#include "prounFactory.h"


proun::App::App() {
    
    ofLogVerbose("App", "constructor");
    
    model = new Model();
    controller = new Controller(model);
    
    mouseController.setup(model);
    
    keyboardController = new KeyboardController();
    keyboardController->setup(controller, model);
    
    ofAddListener(model->selectEvent, this, &proun::App::onSelect);
}

proun::App::~App() {
    ofRemoveListener(model->selectEvent, this, &proun::App::onSelect);
}

void proun::App::setup(string fileName) {
    guiAdapter.setup(model);
    fboAdapter.setup(model);
    
    model->fileName = fileName;
    model->factory = new Factory();
    addNode(Settings::getInstance().settings);

};

void proun::App::initModules() {
    model->modules->setup();
    model->modules->add(new PatchingModule());    
}

void proun::App::update() {
    model->update();
    
    if (Settings::getInstance().needSave == true) {
        guiAdapter.save();
        Settings::getInstance().needSave = false;
    }
    fboAdapter.update();
};

void proun::App::draw() {
    if (Settings::getInstance().doDrawNodes) {
        if (proun::Style::stokeAlpha > 0) {
            ofSetColor(proun::Style::stokeColor, proun::Style::stokeAlpha);
            ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        }
        ofSetColor(255);
        model->draw();
        mouseController.draw();
    }
    
    guiAdapter.draw();
    if (Settings::getInstance().doDrawFbo) fboAdapter.draw();
};



/* --------------------------------------------------------------
 #
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::load() {
    ofLogVerbose("ofxProun", "load " + model->fileName);
    controller->loadFromFile(model->fileName);
}

void proun::App::save() {
    ofLogVerbose("ofxProun", "save " + model->fileName);
    controller->saveToFile(model->fileName);
}


/* --------------------------------------------------------------
 # events
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::onSelect(proun::Model::prounEventArgs &e) {
    model->lastSelected = e.node;
}

void proun::App::onChangeModel(proun::Model &model) {}

//void proun::App::addModule(Module *module) {
//    modulesAdapter.add(module);
//}
/* --------------------------------------------------------------
 # nodes
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::addNode(ofParameterGroup *settings,  bool isOutput) {
    guiAdapter.addNode(settings, isOutput);
}

void proun::App::addNode(FboNode *node,  bool isOutput) {
    ofLogVerbose("proun::App", node->settings->getName());
    guiAdapter.addNode(node->settings, isOutput);
    fboAdapter.addNode(node);
}

/* --------------------------------------------------------------
 # control
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::drawBackground() {
    int t = Settings::getInstance().bg.get();
    ofClear(0);
    ofPushMatrix();
    if (t == 1) {
        ofBackgroundGradient(ofColor(64), ofColor::black);
    } else {
        ofScale(2, 2);
        ofBackgroundGradient(ofColor(180), ofColor(70), OF_GRADIENT_CIRCULAR);
    }
    ofPopMatrix();
}

void proun::App::ckeckLocalConfig() {
    string path = "proun_" + Utils::getHostName() + ".csv";
    ofFile file(path);
    ofLogVerbose("ofApp", "check: " + path);
    if (file.exists()) {
        model->fileName = path;
        ofLogVerbose("ofApp", "load " + path);
    } else {
        ofLogVerbose("ofApp", "load proun.csv");
    }
}


/* --------------------------------------------------------------
 # modes
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::enableButtons() {
    keyboardController->enable();
    keyboardController = new KeyboardController();
    keyboardController->setup(controller, model);
}

void proun::App::disableButtons() {
    keyboardController->disable();
    keyboardController = new BaseKeyboardController();
    keyboardController->setup(controller, model);
}

void proun::App::disableAllButtons() {
    keyboardController->disable();
    keyboardController = new EmptyKeyboardController();
    keyboardController->setup(controller, model);
}


/* --------------------------------------------------------------
 # info
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::App::drawInfo(string externalString, bool append) {
    
    stringstream help;
    help << "fps: " + ofToString(ofGetFrameRate()) + "\n\n";
    help << model->modules->getInfo() + "\n\n";

    if (model->modules->doPresets() == false) {    
        if (keyboardController->isShift) help << "shifting\n\n";
        for (int i = 0; i < model->factory->getTypes().size(); i++) {
            help << ofToString(i) << ":" << model->factory->getTypes()[i] << "\n";
        }
    }
    
    ofSetHexColor(0x333333);
    ofRectangle rect = proun::Style::font->getStringBoundingBox(help.str(), 0, 0);
    ofSetColor(0, 0, 0, 48);
    rect.width += 20;
    rect.height += 20;
    rect.y = ofGetHeight() - rect.getHeight() - 20;
    ofDrawRectangle(rect);
    
    ofSetHexColor(0xffffff);
    
    proun::Style::font->drawString(help.str(), 10, ofGetHeight() - rect.height - 5);
}


