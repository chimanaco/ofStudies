// based on:
// http://formandcode.com/code-examples/visualize-superformula

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void updateFormula();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofPoint* superformula(float m, float n1, float n2, float n3);
        ofPoint superformulaPoint(float m, float n1, float n2, float n3, float phi);
    
        ofxPanel gui;
        ofParameter<int>  sNumber;
        ofParameter<float> speed;
        ofParameter<float> a;
        ofParameter<float> b;
        ofParameter<float>  phiDiv;
        ofParameter<float> newScalarOffset;
        ofParameter<float> scaler;
        ofParameter<int>  m;
        ofParameter<float> n1;
        ofParameter<float> n2;
        ofParameter<float> n3;
    
        const static int POINTNUM = 360;
        int frameCount;
};
