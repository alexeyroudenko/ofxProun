#pragma once
#include "prounModel.h"
#include "prounConnectable.h"
#include "prounSettings.h"

namespace proun {
    
    class Controller
    {
    protected:
        Model *model;
        
        
    public:
        Controller(Model *model_) {
            model = model_;
        }
        
        void breakConnection(string connectionName, Node::Connection connection) {
            vector<NodePtr>::iterator node = model->nodes.begin();
            for ( ; node != model->nodes.end(); ) {
                map<string, Node::Connection>::iterator input = node->get()->inputs.begin();
                for (; input != node->get()->inputs.end();) {
                    string name = input->first;
                    Node::Connection connection2 = input->second;
                    if (name == connectionName) {
                        node->get()->inputs.erase(input);
                        break;
                    } else {
                        ++input;
                    }
                }
                
                ++node;
            }
        }
        
        void deleteSelected() {
            vector<NodePtr>::iterator node = model->nodes.begin();
            for ( ; node != model->nodes.end(); ) {
                if (node->get()->isSelected()) {
                    map<string, Node::Connection>::iterator o = node->get()->outputs.begin();
                    for (; o != node->get()->outputs.end();) {
                        string name = o->first;
                        Node::Connection connection = o->second;
                        breakConnection(name, connection);
                        ++o;
                    }
                    node = model->nodes.erase(node);
                    Model::prounEventArgs args;
                    args.node = node->get();
                    ofNotifyEvent(model->deSelectEvent, args, this);
                } else {
                    ++node;
                }
            }
        }
        
        void clear() {
            model->nodes.clear();
        }
        
        void saveToFile(string fileName) {
            if (Settings::getInstance().doDrawNodes) Settings::getInstance().needSave = true;
            ofBuffer buff;
            for (auto node:model->nodes) {
                ofLogVerbose(node.get()->serialize());
                buff.append(node.get()->serialize() + "\n");
            }
            string del = "[connections]\n";
            buff.append(del);
            for (auto node:model->nodes) {
                buff.append(node.get()->serializeConnections() + "\n");
            }
            ofLogVerbose("Model", buff);
            ofBufferToFile(fileName, buff);
        }
        
        void loadFromFile(string fileName) {
            string path = ofToDataPath(fileName);
            ofFile file(path);
            ofLogVerbose("Model", "path " + file.getAbsolutePath());
            clear();
            bool doConnections = false;
            ofBuffer buff = ofBufferFromFile(file.getAbsolutePath());
            vector<string> strings = ofSplitString(buff.getText(), "\n");
            for (int i = 0; i < strings.size(); i++) {
                string serialized = strings[i];
                if (serialized.size() > 0) {
                    if (strcmp(serialized.c_str(), "[connections]") == 0) {
                        doConnections = true;
                    } else {
                        vector<string> tstrings = ofSplitString(serialized, ";");
                        if (doConnections == false) {
                            string name = tstrings[0];
                            if (model->factory->hasProduct(name)) {
                                NodePtr node = model->factory->createByName(name);
                                node.get()->deSerialize(serialized);
                                model->add(node);
                            }
                        }
                    }
                }
            }
            ofNotifyEvent(model->onLoad, fileName);
            model->update();
            
            loadConnections(fileName);
        }
        
        void loadConnections(string fileName) {
            ofLogVerbose("Model", "loadConnections");
            bool doConnections = false;
            ofBuffer buff = ofBufferFromFile(fileName);
            vector<string> strings = ofSplitString(buff.getText(), "\n");
            for (int i = 0; i < strings.size(); i++) {
                string serialized = strings[i];
                if (serialized.size() > 0) {
                    if (strcmp(serialized.c_str(), "[connections]") == 0) {
                        doConnections = true;
                    } else {
                        vector<string> tstrings = ofSplitString(serialized, ";");
                        if (doConnections == false) {
                            
                        } else {
                            int meuid = ofToInt(tstrings[0]);
                            int touid = ofToInt(tstrings[2]);
                            string mepname = tstrings[1];
                            string topname = tstrings[3];
                            NodePtr me = model->getById(meuid);
                            NodePtr to = model->getById(touid);
                            if (model->hasNode(meuid) && model->hasNode(touid)) {
                                model->connect(Connectable::Connection(to.get(), topname),
                                               Connectable::Connection(me.get(), mepname));
                            }
                        }
                    }
                }
            }
            ofNotifyEvent(model->onLoad, fileName);
        }
    };
}
