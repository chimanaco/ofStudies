#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxGui.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20

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

	ofImage				bgImage;
	ofTrueTypeFont		font;
    ofTrueTypeFont      smallFont;
	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once
    
    // OSC
    ofxOscReceiver receiver;
    
    // OSC
    int current_msg_string;
    string msg_strings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];
    
    float oscFrequency;  // fromVDMX 0.0 or 1.0
    
    ofParameter<float> zDepth;
    ofParameter<float> xNoise;
    ofParameter<float> yNoise;
    ofParameter<int> brightness;
    ofParameter<bool> filled;
    
    ofxPanel gui;

    
private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
    
    string buttonState;
    string potValue;

};

