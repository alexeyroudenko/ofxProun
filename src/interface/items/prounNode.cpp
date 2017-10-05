#include "prounNode.h"

proun::Node::Node(string name_) {
    name = name_;
    uid = ofGetSystemTime();
    setSize(Style::width, Style::height);
}

proun::Node::~Node() {
    ofLogVerbose("ofxProunNode", "destructor");
}

void proun::Node::evaluate() {

}

void proun::Node::setPatching(bool value) {
    patching = value;
}

void proun::Node::draw() {
    Draggable::draw();

    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(ofRectangle::x, ofRectangle::y);

    ofPushMatrix();
    ofTranslate(proun::Style::padding, proun::Style::padding + 7);
    contentDraw();
    ofPopMatrix();

    input.width = width;
    output.width = width;
    
    for (int i = 0; i < input.names.size(); i++) {
        if (patching) {
            ofSetColor(proun::Style::bgColor, proun::Style::bgAlpha);
            ofFill();
            ofDrawRectangle(input.getRect(i));
        }
        ofFill();
        ofDrawCircle(input.getRect(i).getCenter(), proun::Style::round);
    }
    
    for (int i = 0; i < output.names.size(); i++) {
        if (patching) {
            ofSetColor(255, proun::Style::bgAlpha);
            ofFill();
            ofDrawRectangle(output.getRect(i));
        }
        ofSetColor(255);
        ofFill();
        ofDrawCircle(output.getRect(i).getCenter(), proun::Style::round);
    }

    ofPopMatrix();
    ofSetColor(255);
};

void proun::Node::drawInputs(Connectable *node) {
    ofSetColor(255);
    map<string, Node::Connection>::iterator c = node->inputs.begin();
    for (; c != node->inputs.end(); c++) {
        Connectable *node2 = c->second.node;
        ofRectangle r1 = node2->output.getRect(c->second.paramName);
        ofRectangle r2 = node->input.getRect(c->first);
        ofPoint p1 = node2->position + r1.position + (r1.width * .5f);
        ofPoint p2 = node->position + r2.position + (r1.width * .5f);
        smoothStepCurve(p1, p2, 30);
        drawInputs(node2);
    }
}

void proun::Node::contentDraw() {
    ofSetColor(proun::Style::titleColor);
    proun::Style::font.get()->drawString(infoString(), 0, 0);
}

/* --------------------------------------------------------------
 # info
 #
 #
 #
 # -------------------------------------------------------------- */
string proun::Node::infoString() {
    stringstream info;
    info << name +  "\n";
    return info.str();
}

void proun::Node::keyPressed(int key) {
    ofLogVerbose("Node", ofToString(key));
}
