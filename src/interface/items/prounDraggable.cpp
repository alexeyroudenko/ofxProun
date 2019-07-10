#include "prounDraggable.h"


void proun::Draggable::draw() {
    ofSetColor(0, proun::Style::bgAlpha);
    if (hover) ofSetColor(0, proun::Style::hover);
    if (selected) ofSetColor(0, proun::Style::selected);
    ofDrawRectRounded(*this, proun::Style::roundEdges);
};

void proun::Draggable::setHover(bool value) {
    hover = value;
}

bool proun::Draggable::isHover() {
    return hover;
}

void proun::Draggable::setSelected(bool value) {
    bool needSend = hover == value;
    selected = value;
    if (needSend) ofNotifyEvent(onSelect, selected);
}

bool proun::Draggable::isSelected() {
    return selected;
}

void proun::Draggable::setDragging(bool value, int x, int y) {
    bool needSend = hover == value;
    dragging = value;
    pressedPosition.x = x - getX();
    pressedPosition.y = y - getY();
    
}

void proun::Draggable::drag(int x, int y) {
    ofRectangle::setX(x - pressedPosition.x);
    ofRectangle::setY(y - pressedPosition.y);
    moveToNet();
}

void proun::Draggable::addDrag(int dx, int dy) {
    ofRectangle::position.x += dx;
    ofRectangle::position.y += dy;
    moveToNet();
}

void proun::Draggable::moveToNet() {
    if (Style::moveDelta >= 2) {
        int cdx = int(ofRectangle::position.x) % Style::moveDelta;
        int cdy = int(ofRectangle::position.y) % Style::moveDelta;
        setX(ofRectangle::position.x - cdx);
        setY(ofRectangle::position.y - cdy);
    }
}

bool proun::Draggable::isDragging() {
    return dragging;
}

string proun::Draggable::debugString() {
    stringstream info;
    info << "isHover:" + ofToString(isHover(),0) + "\n";
    info << "isSelected:" + ofToString(isSelected()) + "\n";
    info << "isDragging:" + ofToString(isDragging()) + "\n";
    return info.str();
}
