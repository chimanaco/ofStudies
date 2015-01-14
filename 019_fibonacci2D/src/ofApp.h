// Based on:
// http://openprocessing.org/sketch/10433

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void drawReset();
        void calculatePoint(float x, float y, float r, float graden);
    
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
        ofParameter<float> speed;
        ofParameter<float> spacing;
        ofParameter<float> radius;
        ofParameter<float> alpha;
        ofParameter<float> red;
        ofParameter<float> green;
        ofParameter<float> blue;
        ofParameter<float> weight;
        ofParameter<bool> bLine;
        ofParameter<bool> bCircle;
        ofParameter<bool> bFilled;
        ofParameter<bool> bColor;
        ofParameter<bool> bWeightNoise;
        ofParameter<bool> bRadiusNoise;
        ofParameter<bool> bRedNoise;
        ofParameter<bool> bGreenNoise;
        ofParameter<bool> bBlueNoise;
    
        float px;
        float py;
        float r;
        float degree;
        float guldenSnede;
        float lastX;
        float lastY;
        int w;
        int h;
        float frameCount;
        float minSpeed;
        float maxSpeed;
        float minSpacing;
        float maxSpacing;
        float minRadius;
        float maxRadius;
        float minAlpha;
        float maxAlpha;
        float minWeight;
        float maxWeight;
};
