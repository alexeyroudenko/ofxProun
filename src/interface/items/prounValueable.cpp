#include "prounValueable.h"

string proun::Valueable::getName() {
    return name;
}

int proun::Valueable::getUid() {
    return uid;
}

void proun::Valueable::evaluate() {
    
}

bool proun::Valueable::validate() {
    return false;
}

bool proun::Valueable::isDraggableAtPoint(const ofPoint &p) {
    if (input.getIndexAtPoint(p) != -1 || output.getIndexAtPoint(p) != -1) return false;
    return true;
}
