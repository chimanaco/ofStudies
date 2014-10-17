#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

class ofApp:public ofBaseApp{
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

		ofEasyCam cam;
		ofVbo my_vbo;
		ofShader my_shader;
		ofMesh my_mesh;
    
        // OSC
        ofTrueTypeFont font;
        ofxOscReceiver receiver;
        
        // OSC
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        
        string mouseButtonState;
        
        float oscFrequency;  // fromVDMX 0.0 or 1.0
    
        void circleResolutionChanged(int & circleResolution);
    
        ofParameter<float> zDepth;
        ofParameter<ofColor> color;
        ofParameter<ofVec2f> center;
        ofParameter<int> circleResolution;
        ofParameter<bool> filled;
        ofxButton twoCircles;
        ofxButton ringButton;
        ofParameter<string> screenSize;
        
        ofxPanel gui;
};
