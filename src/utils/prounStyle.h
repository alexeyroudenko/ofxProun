#pragma once
#include "ofMain.h"

namespace proun {
    class Style
    {
    public:
        static ofPtr<ofTrueTypeFont> font;
        static ofPtr<ofTrueTypeFont> bigFont;
        static int moveDelta;
        static int round;
        static int roundEdges;
        static int nodeHeader;
        static int nodeConnectionSize;
        static int padding;
        static int stokeColor;
        static int stokeAlpha;
        static int width;
        static int height;
        static int maxCharachters;
        static int titleColor;
        static int textColor;
        static int textPaddingX;
        static int textPaddingY;
        static int bgAlpha;
        static int bgColor;
        static int hover;
        static int selected;
        static void loadFont(string file, int size);
        static void loadBigFont(string file, int size);
        
        static Style& getInstance() {
            static Style INSTANCE;
            return INSTANCE;
        }
        
    private:
        
        Style(){};
        
    };
}

