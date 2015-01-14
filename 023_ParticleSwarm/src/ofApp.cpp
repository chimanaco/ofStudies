#include "ofApp.h"

float frameCount = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    // 画面基本設定
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    
//    ofNoFill();
    ofSetColor(255, 255, 0);
    
    gui.setup();
    gui.add(speed.setup("speed", 8.0, 0.0, 10.0));
    gui.add(size.setup("radius size", 0.1, 0, 10));
    gui.add(bgAlpha.setup("background alpha", 5, 0, 31));
    
    gui.loadFromFile("settings.xml");

    initParticles();
}

//--------------------------------------------------------------
void ofApp::update(){
    t = ofGetElapsedTimef();
    
    frameCount++;
    
    if(frameCount > 200) {
        initParticles();
    }
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        particle[i].resetForce();
        particle[i].addForce( ofVec3f(0, ofSignedNoise(t, i) * 0.1, ofNoise(t, i) * 0.3));
        particle[i].updateForce();
        particle[i].updateSize(ofNoise(t * 0.2, 0.01 * i) * size);
        particle[i].updatePos();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    for (int i = 0; i < CIRCLE_NUM; i++) {
        particle[i].draw();
    }
    cam.end();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::initParticles(){
    ofBackground(0);
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        ofVec3f pos = ofVec3f(0, 0, ofRandom(100));
        ofVec2f vel = ofVec2f(ofRandom(-speed, speed), ofRandom(-speed, speed));
        particle[i].setup(pos, vel);
        particle[i].radius = 5;
    }
    frameCount = 0;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    initParticles();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
