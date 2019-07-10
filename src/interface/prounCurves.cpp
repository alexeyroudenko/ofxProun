#include "prounCurves.h"

void proun::Curves::smoothStepCurve( ofVec2f _start, ofVec2f _end, int _res) {
    ofMesh tmpMesh;
    tmpMesh.setMode( OF_PRIMITIVE_LINE_STRIP );
    for( int k = 0; k < _res; k++ )
    {
        ofVec2f tmpPoint = _start.getInterpolated( _end, k / (float)(_res-1) );
        tmpPoint.y = ofMap( smoothstep(_start.x, _end.x, tmpPoint.x), 0, 1, _start.y, _end.y );
        tmpMesh.addVertex(ofVec3f(tmpPoint.x, tmpPoint.y, 0));
    }
    ofPushStyle();
    ofSetLineWidth(2);
    ofEnableSmoothing();
    tmpMesh.draw();
    ofPopStyle();
}

float proun::Curves::smoothstep(float edge0, float edge1, float x) {
    x = ofClamp( (x - edge0)/(edge1 - edge0), 0, 1); // Scale, and clamp x to 0..1 range
    return x*x*x*(x*(x*6 - 15) + 10); // Evaluate polynomial
}

float proun::Curves::smoothStepInOut( float _t, float _low0, float _high0, float _high1, float _low1 ) {
    float localLow0  = _low0;
    float localHigh0 = _high0;
    float localLow1  = _low1;
    float localHigh1 = _high1;
    return smoothstep( localLow0, localHigh0, _t ) * (1.0f - smoothstep( localHigh1, localLow1, _t ));
}
