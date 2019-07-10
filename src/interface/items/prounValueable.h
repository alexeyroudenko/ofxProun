#pragma once
#include "prounDraggable.h"
#include "prounCurves.h"

using namespace std;

namespace proun {
    
    enum PORT_TYPE {
        PORT_TYPE_INPUT = 0,
        PORT_TYPE_OUTPUT = 1
    };
    
    class IO {
    protected:
    public:
        vector<string> names;
        map<string, ofPtr<ofAbstractParameter>> values;

        int width = 300;
        PORT_TYPE type;
        
        void add(string name) {
            names.push_back(name);
        }
        
        string getName(int index) {
            return names[index];
        }

        ofPtr<ofAbstractParameter> getValue(string oname) {
            if (type == PORT_TYPE_OUTPUT) {
                std::multimap<string, ofPtr<ofAbstractParameter> >::iterator it = values.find(oname);
                ofPtr<ofAbstractParameter> r = it->second;
                return r;
            }
            
            map<string, ofPtr<ofAbstractParameter> >::iterator i = values.find(oname);
            if (i == values.end()) {
                ofLog(OF_LOG_ERROR) << "can't find input value named " << oname << endl;
            }
            return i->second;

        }
        
        template <typename inType>
        inType getValue(string name) {
            ofPtr<ofAbstractParameter> p = getValue(name);
            inType v = dynamic_cast<ofParameter<inType> *>(p.get())->get();
            return v;
        }
        
        void setValue(const string &name, ofPtr<ofAbstractParameter> value) {
            values[name] = value;
        }
        
        int getIndex(const string &name) {
            for (int i = 0; i < names.size(); i++) {
                if (name == names[i]) {
                    return i;
                }
            }
            return -1;
        }
        
        int getIndexAtPoint(const ofPoint &p) {
            for (int i = 0; i < names.size(); i++) {
                if (getRect(i).inside(p))
                    return i;
            }
            return -1;
        }
        
        ofRectangle getRect(const string &name) {
            return getRect(getIndex(name));
        }
        
        ofRectangle getRect(const int &index) {
            if (type == PORT_TYPE_INPUT) {
                int size = proun::Style::nodeConnectionSize;
                return ofRectangle(0, proun::Style::nodeHeader + (size * index), size, size);
            } else {
                int size = proun::Style::nodeConnectionSize;
                return ofRectangle(width - size, proun::Style::nodeHeader + (size * index), size, size);
            }
        }
            
        bool doesAllValuesExist() {
            for (vector<string>::iterator i = names.begin(); i != names.end(); i++) {
                map<string, ofPtr<ofAbstractParameter> >::iterator val = values.find(*i);
                if (val == values.end()) return false;
            }
            return true;
        }
        
    };
    
    
    /* --------------------------------------------------------------
     #
     #
     #
     #
     # -------------------------------------------------------------- */
    class Valueable : public Draggable, protected Curves
    {
        
    protected:
        
        int uid;
        string name;
        
    public:
        
        IO input;
        IO output;
        
        Valueable() {
            input.type = PORT_TYPE_INPUT;
            output.type = PORT_TYPE_OUTPUT;
            input.width = width;
            output.width = width;
        }
        
        int getUid();
        string getName();
        
        bool isDraggableAtPoint(const ofPoint &p);
        
        virtual void evaluate();
        virtual bool validate();
    };
    
    /* --------------------------------------------------------------
     #
     #
     #
     #
     # -------------------------------------------------------------- */
    class Connectable : public Valueable
    {
    public:
        
        struct TempConnection {
            bool active;
            ofPoint p1;
            Connectable *node;
            string paramName;
            PORT_TYPE portType;
        };
        
        struct Connection {
            Connection() {};
            Connection(Connectable *node, string paramName) : node(node), paramName(paramName) {};
            Connectable *node;
            string paramName;
        };
        
        std::map<string, Connection> inputs;
        multimap<string, Connection> outputs;
        
        string debugString() {
            stringstream info;
			std::map<string, Connection>::iterator c = inputs.begin();
            info << "\n\n[inputs]\n";
            for (; c != inputs.end(); c++) {
                ofPtr<ofAbstractParameter> outp = c->second.node->output.getValue(c->second.paramName);
                info << getName() + ":" + c->first + "---" + c->second.node->getName() + ":" + c->second.paramName + "\n";
            }
            
            info << "\n\n[outputs]\n";
			std::map<string, Connection>::iterator ou = outputs.begin();
            for (; ou != outputs.end(); ou++) {
                info << getName() + ":" + ou->first + "----" + ou->second.node->getName() + ":" + ou->second.paramName + "\n";
            }

            return info.str();
        };
    };
}
