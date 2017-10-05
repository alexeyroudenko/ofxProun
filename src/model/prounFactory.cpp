#include "prounFactory.h"

bool proun::Factory::hasProduct(string jname) {
    bool it1 = inSettingsMap.find(jname) != inSettingsMap.end();
    bool it2 = outputSettingsMap.find(jname) != outputSettingsMap.end();
    bool it3 = std::find(std::begin(types), std::end(types), jname) != std::end(types);
    return (it1 || it2 || it3);
}

bool proun::Factory::isSettings(string jname) {
    bool it1 = inSettingsMap.find(jname) != inSettingsMap.end();
    bool it2 = outputSettingsMap.find(jname) != outputSettingsMap.end();
    return (it1 || it2);
}

void proun::Factory::check() {
    ofLogVerbose("Factory ckeck");
}

void proun::Factory::addNodeName(string name) {
    types.push_back(name);
}

void proun::Factory::addInputNode(ofPtr<ofParameterGroup> settings_) {
    string name = settings_.get()->getName();
    types.push_back(name);
    inSettingsMap.insert(std::make_pair(name, settings_));
}

void proun::Factory::addOutputNode(ofPtr<ofParameterGroup> settings_) {
    string name = settings_.get()->getName() + "_o";
    types.push_back(name);
    outputSettingsMap.insert(std::make_pair(name, settings_));
}

vector<string> proun::Factory::getTypes() {
    return types;
}
