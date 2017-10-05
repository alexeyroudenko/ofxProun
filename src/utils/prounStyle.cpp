#include "prounStyle.h"

ofPtr<ofTrueTypeFont> proun::Style::font;
ofPtr<ofTrueTypeFont> proun::Style::bigFont;

int proun::Style::moveDelta = 5;
int proun::Style::width = 80;
int proun::Style::stokeColor = 128;
int proun::Style::stokeAlpha = 64;
int proun::Style::height = 25;
int proun::Style::padding = 3;
int proun::Style::nodeHeader = 13;
int proun::Style::nodeConnectionSize = 10;
int proun::Style::round = 3;
int proun::Style::roundEdges = 5;
int proun::Style::maxCharachters = 16;
int proun::Style::titleColor = 196;
int proun::Style::textColor = 150;
int proun::Style::textPaddingX = 10;
int proun::Style::textPaddingY = 10;
int proun::Style::bgColor = 32;
int proun::Style::bgAlpha = 128;
int proun::Style::selected = 196;
int proun::Style::hover = 64;


void proun::Style::loadFont(string file, int size) {
    font = ofPtr<ofTrueTypeFont>(new ofTrueTypeFont());
    font->load(file, size);
}

void proun::Style::loadBigFont(string file, int size) {
    bigFont = ofPtr<ofTrueTypeFont>(new ofTrueTypeFont());
    bigFont->load(file, size);
}
