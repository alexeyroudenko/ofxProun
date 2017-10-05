#include "prounSerializable.h"

/* --------------------------------------------------------------
 # serialization
 #
 #
 #
 # -------------------------------------------------------------- */
string proun::Serializable::serializeConnections() {
    string connections = "";
    for (auto c:inputs) {
        string meuid = ofToString(getUid());
        string mepname = ofToString(c.first);
        string touid = ofToString(c.second.node->getUid());
        string topname = c.second.paramName;
        string conn = meuid + ";" + mepname + ";" + touid + ";" + topname + ";\n";
        connections = connections + conn;
        
    }
    return connections;
}

string proun::Serializable::serialize() {
    string stringEnd = customSerialize() + ";";
    return name + ";" + ofToString(uid) + ";" + ofToString(x) + ";" + ofToString(y) + ";" + stringEnd;;
}

void proun::Serializable::deSerialize(string serialized) {
    ofLogVerbose("ofxProunNode", "deSerialize: " + serialized);
    vector<string> tstrings = ofSplitString(serialized, ";");
    if (tstrings.size() > 0) {
        name = tstrings[0];
        uid = ofToInt(tstrings[1]);
        setX(ofToInt(tstrings[2]));
        setY(ofToInt(tstrings[3]));
        if (tstrings.size() > 3) customDeSerialize(tstrings[4]);
    }
}

string proun::Serializable::customSerialize() {
    return "";
}

void proun::Serializable::customDeSerialize(string serialized) {}
