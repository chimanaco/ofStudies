/* --------------------------------------------
 
 of_v0.8.4_osx
 based on: an example from "Mastering openFrameworks: Creative Coding Demystified"
 
-------------------------------------------- */

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
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
    
    	//Shader
        ofShader shader;
    
        // OSC
		ofTrueTypeFont font;
		ofxOscReceiver receiver;

        ofSpherePrimitive sphere;
    
        // OSC
        int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		string mouseButtonState;
    
        float oscBeat;  // fromVDMX 0.0 or 1.0
        float oscLFOSine;// fromVDMX 0.0 - 1.0
        float oscTime;
    
        ofParameter<float> angle;
        ofParameter<ofColor> color;
        ofParameter<ofVec2f> center;
        ofParameter<int> circleResolution;
        ofParameter<bool> filled;
        ofxButton twoCircles;
        ofxButton ringButton;
        ofParameter<string> screenSize;
        
        ofxPanel gui;
};
