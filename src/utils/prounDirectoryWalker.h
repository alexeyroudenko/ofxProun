#pragma once

#include "ofMain.h"

namespace proun {
    class DirectoryWalker: public ofFile {
        
        public:
        ofEvent<string> onFileLoad;
        
        ofParameter<int> current;
        string loadedFileName = "";
        string baseName = "";
        string ext = "";
        
        //--------------------------------------------------------------
        void setup(string folder_, string name_ = ""){
            ofSetLogLevel("ofDirectory", OF_LOG_SILENT);
            name = name_;
            folder = folder_;
            current = 0;
            if (name_ != "") {
                loadState();
                loadAt(current);
            }
        }
        
        void loadAt(int number) {
            if (number == -1) loadState();
            string directory = folder;
            if (ext != "") dir.allowExt(ext);
            dir.listDir(directory);
            dir.sort();
            current = number;
            if (dir.size() <= current) current = 0;
            if (dir.size() != 0) {
                string fileName = dir.getPath(current);
                ofFile file(fileName);
                string filePath = file.getAbsolutePath();
                ofLogVerbose("DirectoryWalker", "load at "  + ofToString(current) + " " + filePath);
                baseName = file.getBaseName();
                loadedFileName = fileName;
                ofNotifyEvent(onFileLoad, fileName);
            } else {
                ofLogVerbose("DirectoryWalker", "create empty for: " + dir.getAbsolutePath());
                loadedFileName = "";
                //image = ofImage();
                ofNotifyEvent(onFileLoad, loadedFileName);
            }
        }
        
        int getCurrent() {
            return current;
        }
        
        void loadNext() {
            string directory = folder;
            if (ext != "") dir.allowExt(ext);
            dir.listDir(directory);
            dir.sort();
            
            current++;
            if (dir.size() <= current) current = 0;
            
            string fileName = dir.getPath(current);
            ofFile file(fileName);
            string filePath = file.getAbsolutePath();
            baseName = file.getBaseName();
            ofLogVerbose("DirectoryWalker", "load at "  + ofToString(current) + " " + filePath);
            //ofImage::load(fileName);
            loadedFileName = fileName;
            ofNotifyEvent(onFileLoad, fileName);
        }
        
        void loadPrevious() {
            string directory = folder;
            if (ext != "") dir.allowExt(ext);
            dir.listDir(directory);
            dir.sort();
            
            current--;
            if (current < 0) current = dir.size() - 1;
            
            string fileName = dir.getPath(current);
            ofFile file(fileName);
            string filePath = file.getAbsolutePath();
            baseName = file.getBaseName();
            ofLogVerbose("DirectoryWalker", "load at "  + ofToString(current) + " " + filePath);
            //ofImage::load(fileName);
            loadedFileName = fileName;
            ofNotifyEvent(onFileLoad, fileName);
        }
        
        string getFileName() {
            string directory = folder;
            dir.listDir(directory);
            dir.sort();
            return dir.getPath(current);
        }
        
        void loadState() {
            ofBuffer buffer = ofBufferFromFile("settings/" + name);
            current = ofToInt(buffer.getText());
            ofLogVerbose("DirectoryWalker", "loadState "  + ofToString(current) + " at:" + folder + " name:" + name);
        }
        
        void saveState() {
            ofLogVerbose("DirectoryWalker", "saveState:" + ofToString(current) + " name:" + getFileName() +  " at:" + folder + " name:" + name);
            ofFile file(ofToDataPath("settings/" + name), ofFile::WriteOnly);
            file << ofToString(current);
            file.close();
        }
        
        private:
        string folder = "";
        string name = "";
        ofDirectory dir;
        
    };
}
