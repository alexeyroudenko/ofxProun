#include "prounSelectionController.h"

void proun::SelectionController::setup(Model *model_) {
    model = model_;
    ofAddListener(model->onLoad, this, &SelectionController::onLoad);
}

void proun::SelectionController::draw() {
    if (makeSelection) {
        ofSetColor(255, 32);
        ofFill();
        ofDrawRectangle(rect);
        ofSetColor(255);
        ofNoFill();
        ofDrawRectangle(rect);
        ofFill();
    }
}

void proun::SelectionController::start() {
    //ofLogVerbose("SelectionController", "start");
    doSelection = true;
    startPosition = ofPoint(ofGetMouseX(), ofGetMouseY());
    current = ofPoint(ofGetMouseX(), ofGetMouseY());
}

void proun::SelectionController::finish() {
    //ofLogVerbose("SelectionController", "finish");
    if (doSelection) {
        for (auto node = model->nodes.begin(); node != model->nodes.end(); ++node) {
            bool inside = rect.inside(node->get()->getX(), node->get()->getY());
            node->get()->setSelected(inside);
        };
        
    }
    makeSelection = doSelection = false;
}

void proun::SelectionController::mouseDragged(ofMouseEventArgs &e) {
    if (doSelection) {
        current = ofPoint(ofGetMouseX(), ofGetMouseY());
        makeSelection = true;
        updateRectangle();
    }
};

void proun::SelectionController::mousePressed(ofMouseEventArgs &e) {
    start();
    updateRectangle();
};

void proun::SelectionController::mouseReleased(ofMouseEventArgs &e) {
    current = ofPoint(ofGetMouseX(), ofGetMouseY());
    updateRectangle();
    makeSelection = doSelection = false;
};

void proun::SelectionController::updateRectangle() {
    ofPoint size = current - startPosition;
    rect = ofRectangle(startPosition, size.x, size.y);
}

void proun::SelectionController::deselectAll() {
    for (auto node:model->nodes) {
        node.get()->setSelected(false);
        node.get()->setDragging(false);
        node.get()->setPatching(false);
    };
}

void proun::SelectionController::onLoad(string &fileName) {
    deselectAll();
}
