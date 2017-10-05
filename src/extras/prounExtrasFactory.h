#pragma once

#include "prounFactory.h"
#include "prounHistoryNode.h"
#include "prounNanokontrolNode.h"
namespace proun {
    class ExtrasFactory : public Factory
    {
    public:
        ExtrasFactory() {
            addNodeName("nanokontrol");
            addNodeName("history");
        }
        
        virtual ofPtr<Node> createByName(string jname) override {

            if (strcmp(jname.c_str(), "nanokontrol") == 0)   {
                return ofPtr<NanokontrolNode<float> >(new NanokontrolNode<float>(0));
            }
            
            if (strcmp(jname.c_str(), "history") == 0)   {
                return ofPtr<HistoryNode<float> >(new HistoryNode<float>(0));
            }

            return Factory::createByName(jname);
        }
    };
}
