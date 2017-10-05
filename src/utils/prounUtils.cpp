#include "prounUtils.h"

string proun::Utils::savedHostName;

string proun::Utils::getConfigFileName() {
    return "proun_" + Utils::getHostName() + ".csv";
}

string proun::Utils::getLogFileName() {
    return "proun_" + Utils::getHostName() + ".log";
}

string proun::Utils::getHostName() {
    if (savedHostName.empty() == false) return savedHostName;
    FILE* stream = popen("hostname", "r");
    ostringstream output;
    while(!feof(stream) && !ferror(stream)) {
        char buf[128];
        int bytesRead = fread(buf, 1, 128, stream);
        output.write(buf, bytesRead);
    }
    string result = output.str();
    string dot = ".";
    result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
    ofLogVerbose("host: " + result);
    std::size_t pos = result.find(dot);
    if (pos != -1) {
        result = result.substr(0, pos);
    }
    ofLogVerbose("host: " + result);
    savedHostName = result;
    return result;
}

void proun::Utils::muteLogs() {
    ofSetLogLevel("ofxFlowerNodeGuiAdapter", OF_LOG_SILENT);
    ofSetLogLevel("ofxSettingsGuiAdapter", OF_LOG_SILENT);
    ofSetLogLevel("ofxAssimpModelLoader", OF_LOG_SILENT);
    ofSetLogLevel("ofxMidiOut", OF_LOG_SILENT);
    ofSetLogLevel("ofxMidiIn", OF_LOG_SILENT);
    ofSetLogLevel("ofShader", OF_LOG_SILENT);
    ofSetLogLevel("ofXml", OF_LOG_SILENT);
    ofSetLogLevel("ofFbo", OF_LOG_SILENT);
    ofSetLogLevel("ofxFlowGraph", OF_LOG_SILENT);
    ofSetLogLevel("ofxFlowNode", OF_LOG_SILENT);
    ofSetLogLevel("ofxTrackingFlower", OF_LOG_SILENT);
    ofSetLogLevel("ofxFlowDatAdapter", OF_LOG_SILENT);
    ofSetLogLevel("ofxLitSphere", OF_LOG_SILENT);
    ofSetLogLevel("NanoKontrol2", OF_LOG_SILENT);
    ofSetLogLevel("InSettingsNode", OF_LOG_SILENT);
    ofSetLogLevel("prounGuiAdapter", OF_LOG_SILENT);
    ofSetLogLevel("Pd", OF_LOG_SILENT);
    //ofSetLogLevel("Model", OF_LOG_SILENT);
    ofSetLogLevel("ofxProunNode", OF_LOG_SILENT);
    ofSetLogLevel("ofxFolderImage", OF_LOG_SILENT);
}
