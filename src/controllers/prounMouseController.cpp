#include "prounConnectable.h"
#include "prounMouseController.h"

void proun::MouseController::setup(Model *model_) {
    model = model_;
    selection.setup(model);
    
    ofRegisterMouseEvents(this);
}

void proun::MouseController::draw() {
    if (tempConnection.active) {
        ofDrawLine(tempConnection.p1.x, tempConnection.p1.y, ofGetMouseX(), ofGetMouseY());
    }
    
    if (Settings::getInstance().doSelections) {
        selection.draw();
    }
}


/* --------------------------------------------------------------
 # ofxProun::Mouse
 #
 #
 #
 # -------------------------------------------------------------- */
void proun::MouseController::mouseMoved(ofMouseEventArgs &e) {
    for (auto node:model->nodes) {
        bool hover = node.get()->inside(e.x, e.y);
        node.get()->setHover(hover);
        if (hover == true) {
            ofPoint p = ofPoint(e.x - node.get()->getX(), e.y - node.get()->getY());
            bool draggable = node.get()->isDraggableAtPoint(p);
            node.get()->setPatching(!draggable);
        }
    }
    lastMouse = ofPoint(e.x, e.y);
}

void proun::MouseController::mouseDragged(ofMouseEventArgs &e) {
    //ofLogVerbose("MouseController", "mouseDragged countSelected: " + ofToString(model->getCountSelected()));
    
    if (model->getCountSelected() > 1) {
        // dragging multiple
        ofPoint dm = ofPoint(e.x, e.y) - lastMouse;
        for (auto node:model->nodes) {
            if (node.get()->isSelected()) {
                //ofLogVerbose("MouseController", "mouseDragged addDrag: " + ofToString(dm.x));
                node.get()->addDrag(dm.x, dm.y);
                //ofLogVerbose("MouseController", "drag node");
            }
        }
        lastMouse = ofPoint(e.x, e.y);
        return;
    }
    
    
    if (tempConnection.active == true) {
        //ofLogVerbose("MouseController", "tempConnection active");
        for (auto node:model->nodes) {
            if (node.get()->inside(e.x, e.y)) {
                ofPoint m = ofPoint(e.x, e.y);
                ofPoint p = ofPoint(e.x - node.get()->getX(), e.y - node.get()->getY());
                bool draggable = node.get()->isDraggableAtPoint(p);
                node.get()->setPatching(!draggable);
            } else {
                node.get()->setPatching(false);
            }
        }
        
    } else {
        for (auto node:model->nodes) {
            if (node.get()->isDragging() && Settings::getInstance().doMoves == true) {
                node.get()->drag(e.x, e.y);
                //ofLogVerbose("MouseController", "drag node: " + node.get()->getName());
                
                Model::prounEventArgs args;
                args.node = node.get();
                ofNotifyEvent(model->moveEvent, args, model);
                break;
            }
        };
    }
    
    if (Settings::getInstance().doSelections) selection.mouseDragged(e);
    lastMouse = ofPoint(e.x, e.y);
};



void proun::MouseController::mousePressed(ofMouseEventArgs &e) {
    //ofLogVerbose("MouseController", "mousePressed selected:" + ofToString(model->getCountSelected()));
    
    if (model->getCountSelected() > 1) {
        
        if (model->hasNodeAt(e.x, e.y)) {
            lastMouse = ofPoint(e.x, e.y);
            return;
        }
    }
    
    
    // send all deselections
    for (auto node:model->nodes) {
        bool inside = node.get()->inside(e.x, e.y);
        bool deselected = (inside == false && node.get()->isSelected() == true);
        if (deselected) {
            //ofLogVerbose("MouseController", "sent deSelectEvent " + node.get()->getName());
            node.get()->setSelected(false);
            
            Model::prounEventArgs args;
            args.node = node.get();
            
            if(prounNodeController *v = dynamic_cast<prounNodeController*>(args.node)) {
                v->selectedIndex = -1;
            }
            
            ofNotifyEvent(model->deSelectEvent, args, model);
        }
    };
    
    for (auto node:model->nodes) {
        bool inside = node.get()->inside(e.x, e.y);
        bool deselected = (inside == false && node.get()->isSelected() == true);
        
        if (inside) {
            //ofLogVerbose("MouseController", "setSelected " + node.get()->getName() + " is inside:" + ofToString(inside) + " and stop search");
            node.get()->setSelected(inside);
            break;
        }
    };
    
    
    bool nodeSelected = false;
    for (auto node:model->nodes) {
        if (node.get()->inside(e.x, e.y)) {
            
            ofPoint m = ofPoint(e.x, e.y);
            ofPoint p = ofPoint(e.x - node.get()->getX(), e.y - node.get()->getY());
            
            bool draggable = node.get()->isDraggableAtPoint(p);
            node.get()->setDragging(draggable);
            node.get()->setPatching(!draggable);
            
            if (draggable)
            {
                node.get()->setDragging(node.get()->inside(e.x, e.y), e.x, e.y);
            }
            else
            {
                
                // patching
                int inIndex = node.get()->input.getIndexAtPoint(p);
                int outIndex = node.get()->output.getIndexAtPoint(p);
                
                tempConnection.active = true;
                tempConnection.p1 = m;
                tempConnection.node = node.get();
                
                if (inIndex >= 0) {
                    tempConnection.portType = PORT_TYPE_INPUT;
                    tempConnection.paramName = node.get()->input.getName(inIndex);
                    
                }
                
                if (outIndex >= 0) {
                    tempConnection.portType = PORT_TYPE_OUTPUT;
                    tempConnection.paramName = node.get()->output.getName(outIndex);
                }
            }
        }
        if (node.get()->inside(e.x, e.y)) {
            nodeSelected = true;
            
            ofLogVerbose("MouseController", "sent selectEvent " + node.get()->getName());
            Model::prounEventArgs args;
            args.node = node.get();
            ofNotifyEvent(model->selectEvent, args, model);
            break;
        }
        lastMouse = ofPoint(e.x, e.y);
    };
    
    if (nodeSelected == false) {
        //ofLogVerbose("MouseController", "start");
        if (Settings::getInstance().doSelections) selection.mousePressed(e);
    }
    lastMouse = ofPoint(e.x, e.y);
};

void proun::MouseController::mouseReleased(ofMouseEventArgs &e) {
    
    for (auto node:model->nodes) {
        bool deselected = node.get()->isDragging() == true;
        node.get()->setDragging(false);
        node.get()->setPatching(false);
    };
    
    for (auto node:model->nodes)
    {
        if (node.get()->inside(e.x, e.y))
        {
            ofPoint m = ofPoint(e.x, e.y);
            ofPoint p = ofPoint(e.x - node.get()->getX(), e.y - node.get()->getY());
            if (!node.get()->isDraggableAtPoint(p))
            {
                if (tempConnection.active == true) {
                    
                    int index = -1;
                    if (tempConnection.portType == PORT_TYPE_OUTPUT) {
                        index = node.get()->input.getIndexAtPoint(p);
                    } else {
                        index = node.get()->output.getIndexAtPoint(p);
                    }
                    
                    if (index >= 0) {
                        string paramName = "";
                        if (tempConnection.portType == PORT_TYPE_OUTPUT) {
                            paramName = node.get()->input.getName(index);
                        } else {
                            paramName = node.get()->output.getName(index);
                        }
                        
                        if (tempConnection.portType == PORT_TYPE_OUTPUT) {
                            
                            model->connect(Connectable::Connection(tempConnection.node, tempConnection.paramName),
                                           Connectable::Connection(node.get(), paramName));
                            
                        } else {
                            
                            model->connect(Connectable::Connection(node.get(), paramName),
                                           Connectable::Connection(tempConnection.node, tempConnection.paramName));
                        }
                    }
                    
                }
            }
            break;
        }
    }
    
    tempConnection.active = false;
    
    if (Settings::getInstance().doSelections) selection.finish();
};

void proun::MouseController::mouseScrolled(ofMouseEventArgs &e){};
void proun::MouseController::mouseEntered(ofMouseEventArgs &e){};
void proun::MouseController::mouseExited(ofMouseEventArgs &e){};
