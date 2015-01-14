#include "ofApp.h"

float frameCount = 0;

//--------------------------------------------------------------
void ofApp::setup(){
    // ‰æ–ÊŠî–{Ý’è
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    
    // load the texure
    ofDisableArbTex();
    ofLoadImage(texture, "dot.png");
    
    //ofNoFill();
    ofSetColor(255, 255, 0);
    
    gui.setup();
    gui.add(refresh.setup("refresh", 100, 100, 3000));
    gui.add(speed.setup("speed", 8.0, 0.0, 20.0));
    gui.add(defSize.setup("Default size", 10, 1, 20));
    gui.add(size.setup("radius size", 0.1, 0, 10));
    gui.add(forceX.setup("FORCE X", 0.01, 0, 1));
    gui.add(forceY.setup("FORCE Y", 0.01, 0, 1));
    gui.add(forceZ.setup("FORCE Z", 0.01, 0, 1));
    gui.add(forceSeedX.setup("FORCE SEED X", 0.01, 0, 1));
    gui.add(forceSeedY.setup("FORCE SEED Y", 0.01, 0, 1));
    gui.add(forceSeedZ.setup("FORCE SEED Z", 0.01, 0, 1));
    gui.add(colorStart.setup("C1", 0.1, 0, 1));
    gui.add(colorEnd.setup("C2", 0.4, 0, 1));
    gui.add(shape.setup("PARTICLE SHAPE", 0, 0, 3));
    
    gui.loadFromFile("settings.xml");
    
    // emerald
    material.setShininess(76.8);
    material.setAmbientColor(ofColor(5.4825, 44.4975, 5.4825, 255));
    material.setDiffuseColor(ofColor(19.2984, 156.6312, 19.2984, 255));
    material.setSpecularColor(ofColor(161.415, 185.591805, 161.415, 255));
    
	light.enable();
    initParticles();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
    t = ofGetElapsedTimef();
    
    frameCount++;
    
    if(frameCount > refresh) {
        initParticles();
    }
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        particle[i].resetForce();
        particle[i].addForce( ofVec3f(ofSignedNoise(t, i * forceSeedX) * forceX, ofSignedNoise(t, i * forceSeedY) * forceY, ofSignedNoise(t, i * forceSeedZ) * forceZ));
        particle[i].updateForce();
        particle[i].updateSize(ofNoise(t * 0.2, 0.01 * i) * size);
        particle[i].updatePos();
        particle[i].updateColor(colorStart, colorEnd);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();

    cam.begin();
    material.begin();
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        particle[i].draw();
    }

    material.end();

    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::initParticles(){
    ofBackground(0);
    
    for (int i = 0; i < CIRCLE_NUM; i++) {
        ofVec3f pos = ofVec3f(0, 0, 0);
        //ofVec3f pos = ofVec3f(0, 0, ofRandom(100));
        ofVec2f vel = ofVec2f(ofRandom(-speed, speed), ofRandom(-speed, speed));
        particle[i].setup(pos, vel, defSize);
        particle[i].radius = defSize;
        particle[i].shape = shape;
        particle[i].texture = texture;
    }
    
    colorStart = ofRandom(1);
    colorEnd = ofRandom(1);
    
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
