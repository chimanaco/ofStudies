// based on:
// http://formandcode.com/code-examples/visualize-superformula

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTween.h"

//#include "ofxUI.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
        void drawShape();
        void updateShape();
    
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
    
        int frameCount;
        float t;
        
        vector <ofVec2f> points;
        vector <ofVec3f> colors;
        vector <ofVec2f> sizes;
        ofVbo vbo;
        ofMesh mesh;
        ofShader shader;
        ofEasyCam cam;
    
        ofxTween tweenA;
        ofxTween tweenB;
        ofxTween tweenM;
        ofxTween tweenN1;
        ofxTween tweenN2;
        ofxTween tweenN3;
        ofxEasingExpo easingexpo;
    
        ofxPanel gui;
        ofParameter<int>  sNumber;
        ofParameter<float> speed;
        ofParameter<float> a;
        ofParameter<float> b;
        ofParameter<float>  phiDiv;
        ofParameter<float> newScalarOffset;

        ofParameter<float> scaler;
        ofParameter<float>  m;
        ofParameter<float> n1;
        ofParameter<float> n2;
        ofParameter<float> n3;
        ofParameter<float> duration;
        ofParameter<float> stop;
        ofParameter<int> fadeAlpha;
        ofParameter<float> lineWidth;
        ofParameter<int> POINTNUM;
        ofxButton readShader;

};

void setNormals( ofMesh &mesh );

