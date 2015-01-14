// forked from: http://openprocessing.org/sketch/3897

#pragma once

#include "ofMain.h"
#include "ofxGui.h"


#include "Particle.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofxPanel gui;    
        ofParameter<float> rx;
        ofParameter<float> ry;
        ofParameter<float> mx;
        ofParameter<float> my;
        ofParameter<float> px;
        ofParameter<float> py;
        ofParameter<float> ox;
        ofParameter<float> oy;
    
        ofFbo maskFbo;
    
    vector<Particle> particles;
    
        int w;
        int h;
    
};
