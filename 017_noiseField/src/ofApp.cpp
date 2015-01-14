#include "ofApp.h"

int NUM_PARTICLES = 10000;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    
    gui.add(rx.set( "rx", 20, -50, 50 ));
    gui.add(ry.set( "ry", 20, -50, 50 ));
    gui.add(mx.set( "mx", 10, 1, 500 ));
    gui.add(my.set( "my", 10, 1, 500 ));
    gui.add(px.set( "px", 100, 1, 500 ));
    gui.add(py.set( "py", 100, 1, 500 ));
    gui.add(ox.set( "ox", 0.5, -1, 1 ));
    gui.add(oy.set( "oy", 0.5, -1, 1 ));

    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        Particle p;
        p.setup(ofVec2f(ofRandom(w),ofRandom(h)), ofVec2f(0,0));
        particles.push_back(p);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    w = ofGetWidth();
    h = ofGetHeight();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].updateVelocity(mouseX, mouseY, rx, ry, mx, my, px, py, ox, oy);
        particles[i].update(w, h);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,0,0,3);
    ofFill();
    ofRect(0, 0, w, w);
    ofSetColor(255,255,255,50);
    
//    maskFbo.begin(); //type ofFbo
//    ofClear(0,100);
//    camMesh.draw(); //type ofMesh
    
    float t = ofGetElapsedTimef();
    
//    glLineWidth(cos(t)*2);
    
    for(int i = 0; i < NUM_PARTICLES; i++)
    {
        particles[i].draw();
    }

//    maskFbo.end();

    
    // GUI
    //ofDisableDepthTest(); // for 3D
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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