#pragma once
#include "ofMain.h"
#include "ofxProun.h"
#include "prounUtils.h"

namespace proun {
    
    class Utils
    {
    public:
        
        static string savedHostName;
        
        static string getConfigFileName();
        static string getLogFileName();
        static string getHostName();
        static void muteLogs();
    };
}
