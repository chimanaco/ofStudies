#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void initParticles();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    float t;
    ofEasyCam cam;
    ofLight light;
    ofMaterial material;
    ofTexture texture;
    ofShader shader;

    // �`�悷��~�̐����w��
    static const int CIRCLE_NUM = 200
    ;
    
    // �p�[�e�B�N���N���X���C���X�^���X��
    Particle particle[CIRCLE_NUM];
    
    ofxPanel gui;
    ofxIntSlider refresh;
    ofxFloatSlider speed;
    ofxFloatSlider defSize;
    ofxFloatSlider size;
    ofxFloatSlider forceX;
    ofxFloatSlider forceY;
    ofxFloatSlider forceZ;
    ofxFloatSlider forceSeedX;
    ofxFloatSlider forceSeedY;
    ofxFloatSlider forceSeedZ;
    ofxFloatSlider colorStart;
    ofxFloatSlider colorEnd;
    ofxIntSlider shape;
};
