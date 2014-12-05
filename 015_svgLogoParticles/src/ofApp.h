#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxPanel gui;
    ofParameter<float> speed;
    ofParameter<int> margin;
    ofParameter<int> numbers;
    ofParameter<int> hueSpeed;
    ofParameter<float> saturation;
    ofParameter<float> brightness;
    ofParameter<float> depth;
    ofParameter<float> xOff;
    ofParameter<float> sizeOff;
    ofParameter<float> tOff;
    
    ofxSVG svg;
    float step;
    vector<ofPolyline> outlines;
    vector <ofVec2f> points;
    vector <ofVec3f> sizes;
    vector <float> verticesX;
    vector <float> verticesY;
    vector <float> verticesZ;

    ofVbo vbo;
    ofShader shader;
    ofTexture texture;
    ofEasyCam cam;
    
    ofColor color;
    
};
