#include "prounModel.h"
#include "prounSettings.h"

void proun::Model::add(NodePtr nodePtr) {
    nodePtr.get()->setPatching(false);
    nodePtr.get()->setSelected(false);
    nodePtr.get()->setDragging(false);
    nodes.push_back(nodePtr);
}

void proun::Model::update() {
    updateValuables();
};

void proun::Model::updateValuables() {
    for (auto node:nodes) {
        if (node.get()->outputs.size() == 0) {
            if (node.get()->inputs.size() == 0) {
                if (node.get()->validate()) {
                    node.get()->evaluate();
                }
            } else {
                evaluateInputs(node.get());
            }
        } else {
            
            if (node.get()->validate()) {
                node.get()->evaluate();
            }
        }
    }
}

void proun::Model::evaluateInputs(Connectable *node) {
    map<string, Node::Connection>::iterator c = node->inputs.begin();
    for (; c != node->inputs.end(); c++) {
        evaluateInputs(c->second.node);
        ofPtr<ofAbstractParameter> outp = c->second.node->output.getValue(c->second.paramName);
        node->input.setValue(c->first, outp);
        if (node->validate()) {
            node->evaluate();
        }
    }
}


void proun::Model::draw() {
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        it->get()->draw();
        if (it->get()->outputs.size() == 0) {
            it->get()->drawInputs(it->get());
        }
    }
};

bool proun::Model::hasNode(int uid) {
    for (auto node:nodes) {
        if (node.get()->getUid() == uid) return true;
    }
}

proun::NodePtr proun::Model::getById(int uid) {
    for (auto node:nodes) {
        if (node.get()->getUid() == uid) return node;
    }
}

bool proun::Model::hasNodeAt(int x, int y) {
    for (auto node = nodes.begin(); node != nodes.end(); ++node) {
        bool inside = node->get()->inside(x, y);
        if (inside) return true;
    }
    return false;
}

bool proun::Model::hasNode(string name) {
    for (auto node = nodes.begin(); node != nodes.end(); ++node) {
        if (node->get()->getName().compare(name) == 0) return true;
    }
    return false;
}

proun::NodePtr proun::Model::getByName(string name) {
    for (auto node = nodes.begin(); node != nodes.end(); ++node) {
        if (node->get()->getName().compare(name) == 0) return *node;
    }
}

int proun::Model::getCountSelected() {
    int value = 0;
    for (auto node = nodes.begin(); node != nodes.end(); ++node) {
        if (node->get()->isSelected()) value++;
        
    }
    return value;
}
