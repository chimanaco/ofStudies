#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofCamera cam;
    
    ofParameter<float> speed;
    ofParameter<float> cameraXRadius;
    ofParameter<float> cameraZRadius;
    ofxPanel gui;
    
    ofMaterial material;
    ofImage bg;
    ofImage texture;
    
    ofLight pointLight;
    ofLight pointLight2;
    ofLight pointLight3;
};
