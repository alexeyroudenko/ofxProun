#include "prounKeyboardController.h"
#include "prounSettings.h"

void proun::EmptyKeyboardController::setup(Controller *controller_, Model *model_) {
    controller = controller_;
    model = model_;
    ofRegisterKeyEvents(this);
}

void proun::EmptyKeyboardController::keyPressed(ofKeyEventArgs &e) {
}

void proun::EmptyKeyboardController::keyReleased(ofKeyEventArgs &e) {
    Settings::getInstance().needSave = false;
}

void proun::EmptyKeyboardController::disable() {
    ofUnregisterKeyEvents(this);
}

void proun::EmptyKeyboardController::enable() {
    ofRegisterKeyEvents(this);
}

void proun::BaseKeyboardController::keyPressed(ofKeyEventArgs &e) {
    
    if (e.key == '`') isShift = !isShift;
    if (e.key == '.') isShift = !isShift;
    
    Settings::getInstance().keyPressed(e.key);

    if (e.key == 127) controller->deleteSelected();
    
    if (e.key == 63254) std::exit(0);
    if (e.key == 150) std::exit(0);
    if (e.key == 'q') std::exit(0);
    if (e.key == 'f') ofToggleFullscreen();
    
    //ofLogVerbose("KeyboardController", ofToString(e.key));
}

void proun::KeyboardController::keyPressed(ofKeyEventArgs &e) {
    
    //if (e.key == 'k') model->loadConnections(model->fileName);
    
    super::keyPressed(e);
    
    if (e.key == 'l') controller->loadFromFile(model->fileName);
    if (e.key == 's') controller->saveToFile(model->fileName);
    if (e.key == 'n') controller->clear();
    
    if (model->getCountSelected() == 1) {
        model->lastSelected->keyPressed(e.key);
    }
    
    if (Settings::getInstance().doDrawNodes &&
        Settings::getInstance().info == 1) {
        unsigned idx = e.key - '0';
        if (idx < model->factory->getTypes().size() && idx < 10) {

            if (isShift) {
                idx += 10;
                if (idx < model->factory->getTypes().size()) {
                    if (Settings::getInstance().doCreations) createByNumber(idx);
                }
            } else {
                if (Settings::getInstance().doCreations) createByNumber(idx);
            }
        };
    }
    
    if (model->getCountSelected() > 1) {
        vector<NodePtr>::iterator node = model->nodes.begin();
        for ( ; node != model->nodes.end(); ) {
            if (node->get()->isSelected()) {
                float x = node->get()->getX();
                float y = node->get()->getY();
                if (e.key == OF_KEY_LEFT) node->get()->setX(x - 10);
                if (e.key == OF_KEY_RIGHT) node->get()->setX(x + 10);
                if (e.key == OF_KEY_UP) node->get()->setY(y - 10);
                if (e.key == OF_KEY_DOWN) node->get()->setY(y + 10);
            }
            node++;
        }
    }
}

void proun::KeyboardController::createByNumber(int number) {
    string name = model->factory->getTypes()[number];
    ofPtr<Node> nodePtr = model->factory->createByName(name);
    model->add(nodePtr);
    nodePtr.get()->setPosition(400, 100 + number * (proun::Style::height + 10));
}
