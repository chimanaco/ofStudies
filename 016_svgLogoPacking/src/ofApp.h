#pragma once

#include "ofMain.h"
#include "ofxSvg.h"

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
		
        ofxSVG svg;
        float step;
        vector<ofPolyline> outlines;

        ofColor color;
        int w;
        int h;
        int xOrigin;
        int yOrigin;
        float len;
        const static int cols = 600;
        const static int rows = 600;

        bool myArray[cols][rows];
        bool okToDrawSquare;

        float logoW;
        float logoH;
        float ratio;
    
        int hueSpeed;
};
