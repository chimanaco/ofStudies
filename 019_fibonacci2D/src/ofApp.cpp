#include "ofApp.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    
    guldenSnede = ((sqrt(5) - 1 ) / 2);
    lastX = 0;
    lastY = 0;
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    frameCount = 0;
    
    px = w/2;
    py = h/2;
    
    minSpeed = 3;
    maxSpeed = 40;
    minSpacing = 5;
    maxSpacing = 30;
    minRadius = 3;
    maxRadius = 100;
    minAlpha = 50;
    maxAlpha = 200;
    minWeight = 1;
    maxWeight = 20;
    
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    
    gui.add(speed.set( "speed", 7, minSpeed, maxSpeed ));
    gui.add(spacing.set( "spacing", 30, minSpacing, maxSpacing ));
    gui.add(radius.set( "radius", 3, minRadius, maxRadius ));
    gui.add(weight.set( "weight", 1, minWeight, maxWeight ));
    gui.add(alpha.set( "alpha", 120, minAlpha, maxAlpha ));
    gui.add(red.set( "red", 255, 0, 255 ));
    gui.add(green.set( "green", 255, 0, 255 ));
    gui.add(blue.set( "blue", 255, 0, 255 ));
    gui.add(bFilled.set( "bFilled", true ));
    gui.add(bLine.set( "bLine", true ));
    gui.add(bCircle.set( "bCircle", false ));
//    gui.add(bColor.set( "bColor", true ));
    gui.add(bWeightNoise.set( "bWeightNoise", false ));
    gui.add(bRadiusNoise.set( "bRadiusNoise", false ));
    gui.add(bRedNoise.set( "bRedNoise", true ));
    gui.add(bGreenNoise.set( "bGreenNoise", false ));
    gui.add(bBlueNoise.set( "bBlueNoise", false ));
}

//--------------------------------------------------------------
void ofApp::update(){
    w = ofGetWidth();
    h = ofGetHeight();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    //float t = ofGetElapsedTimef() * speed;
    frameCount++;
    
    if(r > w || frameCount > 600) {
        drawReset();
    }
    
    if(!bFilled) {
        ofNoFill();
    }
    
    float t = frameCount * speed;

    // line weight
    if(bWeightNoise) {
        weight = ofNoise(t * 0.001) * maxWeight;
    }
    glLineWidth(weight);
    
    // line weight
    if(bRadiusNoise) {
        radius = ofNoise(t * 0.0015) * (maxRadius - minRadius) + minRadius;
    }
    
    if(bRedNoise) {
        red = ofNoise(t * 0.002) * 255;
    }
    
    if(bGreenNoise) {
        green = ofNoise(t * 0.002) * 255;
    }
    
    if(bBlueNoise) {
        blue = ofNoise(t * 0.002) * 255;
    }
    
    
    lastX = px;
    lastY = py;

//    if(bColor){
    ofSetColor(red, green, blue, alpha);
//    }
    
    degree = (t * guldenSnede) * 360;
    r = sqrt(t) * spacing;
    calculatePoint(w / 2, h / 2, r, fmod(degree, 360));
    
    if(bLine){
        if (frameCount != 0) {
            ofLine(lastX, lastY, px,py);
        }
    }
    
    if(bCircle){
        ofCircle(px, py, radius);
    }
    
    
    
    

    
    //draw framerate for fun
    ofSetColor(255);
    string msg = "count: " + ofToString(frameCount, 2);
    ofDrawBitmapString(msg, 10, 20);
    
    
    
    // GUI
    //ofDisableDepthTest(); // for 3D
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::calculatePoint(float x, float y, float r, float graden){
    px = x + cos(ofDegToRad(graden)) * (r/2);
    py = y + sin(ofDegToRad(graden)) * (r/2);
}

//--------------------------------------------------------------
void ofApp::drawReset(){
    // position
    lastX = 0;
    lastY = 0;
    px = 0;
    py = 0;
    r = 0;
    frameCount = 0;
    
    // parameter
    speed = ofRandom(minSpeed, maxSpeed);
    spacing = ofRandom(minSpacing, maxSpacing);
    alpha = ofRandom(minAlpha, maxAlpha);
    
    // fill or nofill
    bFilled = round(ofRandom(0, 1));
    
    // line or circle
    bLine = round(ofRandom(0, 1));
    
    if(!bLine) {
        bCircle = true;
    } else {
        bCircle = false;
    }
    
    // weight
    bWeightNoise = round(ofRandom(0, 1));
    
    if(!bWeightNoise) {
        weight = ofRandom(minWeight, maxWeight);
    }

    // point radius
    bRadiusNoise = round(ofRandom(0, 1));
    
    if(!bRadiusNoise) {
        radius = ofRandom(minRadius, maxRadius);
    }
    
    // color
    bRedNoise = bGreenNoise = bBlueNoise = false;
    int colorNoise = round(ofRandom(0, 2));
    if(colorNoise == 0) {
        bRedNoise = true;
    } else if(colorNoise == 1){
        bGreenNoise = true;
    } else {
        bBlueNoise = true;
    }
    
    if(!bRedNoise) {
        red = ofRandom(0, 255);
    }

    if(!bGreenNoise) {
        green = ofRandom(0, 255);
    }

    if(!bBlueNoise) {
        blue = ofRandom(0, 255);
    }
    
    // clear with black
    ofSetColor(0,0,0,255);
    ofFill();
    ofRect(0, 0, w, h);
    
    ofSetColor(255);
        string msg = "count: " + ofToString(colorNoise, 2);
        ofDrawBitmapString(msg, 10, 20);
    
    // color or white
//    bColor = round(ofRandom(0, 1));
//    if(!bColor) {
//        ofSetColor(255, ofRandom(0, 255));
//    }
//
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