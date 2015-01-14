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
    
    // 描画する円の数を指定
    static const int CIRCLE_NUM = 400;
    
    // パーティクルクラスをインスタンス化
    Particle particle[CIRCLE_NUM];
    
    ofxPanel gui;
    ofxFloatSlider speed;
    ofxFloatSlider size;
    ofxFloatSlider bgAlpha;
};
