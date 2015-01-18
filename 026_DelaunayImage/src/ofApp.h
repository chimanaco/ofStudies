// https://github.com/kamend/KinectDelaunay

#pragma once

#include "ofMain.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{
  public:
    void setup();
    void update();
    void draw();
	void initDelaunay();
    bool sample(ofVec2f p);
	
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
	ofVbo vbo;
    ofxDelaunay del;
	ofMesh mesh;

	vector<ofVec2f> particles;
	ofImage img;
	int frameCount;
	int total;
	int w;
	int h;
	int margin;

	ofxPanel gui;
    ofParameter<float> ratio;
    ofParameter<int> maxCount;
    ofParameter<int> size;
    ofParameter<int> shapes;
};
