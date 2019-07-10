#include "prounGuiAdapter.h"
#include "prounSettings.h"

void proun::GuiAdapter::setup(Model *model_) {
    ofxGuiSetDefaultHeight(14);
    ofxGuiSetFont("fonts/iflash-502.ttf", 6);
    model = model_;
    ofAddListener(model->selectEvent,   this, &GuiAdapter::onSelect);
    ofAddListener(model->deSelectEvent, this, &GuiAdapter::onDeSelect);
    ofAddListener(model->moveEvent,     this, &GuiAdapter::onMove);
}

void proun::GuiAdapter::addNode(ofParameterGroup *settings, bool isOutput) {
    string name = settings->getName();    
    ofLogVerbose("ofxSettingsGuiAdapter", "add>: " + name);
    string fileName = "settings/node_" + name + ".xml";

    ofPtr<ofParameterGroup> ptr = ofPtr<ofParameterGroup>(settings);
    ptrs.push_back(ptr);
    
    if (isOutput == true) {
        model->factory->addOutputNode(ptr);
    } else {
        model->factory->addInputNode(ptr);
    }

    guis[name] = new ofxPanel();
    guis[name]->setup(*settings, fileName);
    guis[name]->loadFromFile(fileName);
    guis[name]->setPosition(ofGetWidth() - Style::width * (i+1), ofGetHeight() / 2 - guis[name]->getHeight() / 2);
    i++;
    
    ofLogVerbose("ofxSettingsGuiAdapter", "add<: " + name);
    
    //ofLogVerbose("GuiAdapter", "added: " + name);
}

void proun::GuiAdapter::draw() {
    if (selected != "" && Settings::getInstance().doDrawNodes) {
        guis[selected]->draw();
    }
    
    if (Settings::getInstance().showGUIS) {
        for (auto p:guis) {
            p.second->draw();
        }
    }
}

void proun::GuiAdapter::load() {
    ofLogVerbose("ofxSettingsGuiAdapter", "load gui");
    for(map<string,ofxPanel*>::iterator it = guis.begin(); it != guis.end(); it++ ){
        string fileName = "settings/node_" + it->first + ".xml";
        it->second->loadFromFile(fileName);
    }
}

void proun::GuiAdapter::save() {
    ofLogVerbose("ofxSettingsGuiAdapter", "save gui");
    for(map<string,ofxPanel*>::iterator it = guis.begin(); it != guis.end(); it++ ){
        string fileName = "settings/node_" + it->first + ".xml";
        it->second->saveToFile(fileName);
    }
}


/* --------------------------------------------------------------
 # events
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::GuiAdapter::onSelect(proun::Model::prounEventArgs &e) {
    string lastName = selected;
    string name = e.node->getName();
    ofLogVerbose("GuiAdapter", "onSelect: " + selected);
    if (strcmp(lastName.c_str(), name.c_str()) == 0) {
        ofLogVerbose("GuiAdapter", "onSelect second");
        doGui = true;
    }
    
    auto iot = guis.find(name);
    if (iot != guis.end()) {
        if (iot->second->getNumControls() > 0) {
            selected = name;
            ofLogVerbose("GuiAdapter", "onSelect: " + selected);
            guis[name]->setPosition(e.node->x + e.node->width + 10, e.node->y);
        }
    }
}

void proun::GuiAdapter::onDeSelect(proun::Model::prounEventArgs &e) {
    ofLogVerbose("GuiAdapter", "onDeSelect: " + e.node->getName());
    selected = "";
}

void proun::GuiAdapter::onMove(proun::Model::prounEventArgs &e) {
    string name = e.node->getName();
    auto iot = guis.find(name);
    if (iot != guis.end()) {
        selected = name;
        guis[name]->setPosition(e.node->x + e.node->width + 10, e.node->y);
    }
}
