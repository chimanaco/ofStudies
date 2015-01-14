// http://paulbourke.net/geometry/supershape/
// http://en.wikipedia.org/wiki/Superformula
// forked from: http://supershape.ahoi.in/
// https://www.gnu.org/software/octave/index.html

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"
#include "ofxTween.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
		void loadShader();
		void loadSettingXML(int num);
		void objectUpdate();
        void updateShape();
    
        ofImage texture;
        ofMaterial material;
        ofFloatColor color;
        ofEasyCam cam;
        ofVbo vbo;
        ofShader shader;
        ofMesh mesh;
        ofLight light;
    
        float et;
        float step;
        int total;
        float angle;
        int frameCount;
    
        ofxTween tweenRadius;
        ofxTween tweenA1;
        ofxTween tweenB1;
        ofxTween tweenM1;
        ofxTween tweenN11;
        ofxTween tweenN21;
        ofxTween tweenN31;
        ofxTween tweenA2;
        ofxTween tweenB2;
        ofxTween tweenM2;
        ofxTween tweenN12;
        ofxTween tweenN22;
        ofxTween tweenN32;
        ofxTween tweenAlpha;
        ofxTween tweenBeta;
        ofxEasingExpo easingexpo;
    
        void shaderNumberChanged(int & shaderNumber);
    
        ofxPanel gui;
        ofParameter<int> radius;
        ofParameter<float> a1;
        ofParameter<float> b1;
        ofParameter<float> m1;
        ofParameter<float> n11;
        ofParameter<float> n21;
        ofParameter<float> n31;
        ofParameter<float> a2;
        ofParameter<float> b2;
        ofParameter<float> m2;
        ofParameter<float> n12;
        ofParameter<float> n22;
        ofParameter<float> n32;
        ofParameter<float> alpha;
        ofParameter<float> beta;
        ofParameter<float> lightX;
        ofParameter<float> lightY;
        ofParameter<float> lightZ;
        ofParameter<int> drawType;
        ofParameter<float> pointSize;
        ofParameter<bool> rotation;
        ofParameter<bool> bShader;
        ofParameter<int> shaderNumber;
        ofParameter<int> shapeNumber;
        ofParameter<float> duration;
        ofParameter<float> stop;
        ofParameter<bool> bChanger;
};

//Universal function which sets normals
//for the triangle mesh
void setNormals( ofMesh &mesh );
