#pragma once
#include "ofMain.h"
#include "prounStyle.h"

namespace proun {
    
    class Curves
    {
    public:
        void smoothStepCurve( ofVec2f _start, ofVec2f _end, int _res = 30 );
        float smoothstep(float edge0, float edge1, float x);
        float smoothStepInOut( float _t, float _low0, float _high0, float _high1, float _low1 );
    };
};
