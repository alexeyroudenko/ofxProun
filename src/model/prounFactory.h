#pragma once

#include "prounValueNode.h"
#include "prounAddNode.h"
#include "prounMultiplyNode.h"
#include "prounTimeNode.h"
#include "prounFadeNode.h"
#include "prounLerpNode.h"
#include "prounLFONode.h"
#include "prounInSettingsNode.h"
#include "prounOutSettingsNode.h"


namespace proun {
    class Factory
    {
        
        template<typename T>Node *createInstance() {return new T;}
        typedef std::map<std::string, Node*(*)()> map_type;
        
    private:
        map_type map;
        
    public:
        
        void check();
        bool hasProduct(string name);
        bool isSettings(string name);
        void addNodeName(string name);
        void addInputNode(ofPtr<ofParameterGroup> settings_);
        void addOutputNode(ofPtr<ofParameterGroup> settings_);
        
        virtual vector<string> getTypes();
        
        
        virtual ofPtr<Node> createByName(string jname) {
            if (strcmp(jname.c_str(), "value") == 0)   {
                return ofPtr<ValueNode<float> >(new ValueNode<float>(jname.c_str(), 0));
            }
            
            if (strcmp(jname.c_str(), "fade") == 0)   {
                return ofPtr<FadeNode<float> >(new FadeNode<float>(jname.c_str(), 0));
            }
            
            if (strcmp(jname.c_str(), "add") == 0) {
                return ofPtr<AddNode>(new AddNode(jname.c_str()));
            }
            
            if (strcmp(jname.c_str(), "multiply") == 0)       {
                return ofPtr<MultiplyNode>(new MultiplyNode(jname.c_str()));
            }
            
            if (strcmp(jname.c_str(), "time") == 0)       {
                return ofPtr<TimeNode<float> >(new TimeNode<float>(jname.c_str(), 0));
            }
            
            if (strcmp(jname.c_str(), "lfo") == 0)       {
                return ofPtr<LFONode<float> >(new LFONode<float>(jname.c_str(), 0));
            }
            
            if (strcmp(jname.c_str(), "lerp") == 0)       {
                return ofPtr<LerpNode<float>>(new LerpNode<float>(jname.c_str()));
            }
            
            
            auto it = inSettingsMap.find(jname);
            if (it != inSettingsMap.end()) {
                return ofPtr<InSettingsNode<ofParameterGroup>>(new InSettingsNode<ofParameterGroup>(jname, it->second));
            }
            
            auto iot = outputSettingsMap.find(jname);
            if (iot != outputSettingsMap.end()) {
                return ofPtr<OutSettingsNode<ofParameterGroup>>(new OutSettingsNode<ofParameterGroup>(jname, iot->second));
            }
        }
        
    protected:
        std::map<string,ofPtr<ofParameterGroup>> inSettingsMap;
        std::map<string,ofPtr<ofParameterGroup>> outputSettingsMap;
        vector<string> types = {"value", "add", "time", "lfo", "multiply", "fade", "lerp"};
    };
}
