// forked from http://www.openprocessing.org/sketch/156587

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    ofSetBackgroundAuto(false);

    logoW = 701.977;
    logoH = 75.083;
    ratio = logoH / logoW;

    len = 40;
    okToDrawSquare = true;
    
    hueSpeed = 1;
    
    w = ofGetWidth();
    h = ofGetHeight();
    
    // Initialize 2D array values
    for (int x = 0; x < cols; x++) {
        for (int y = 0; y < rows; y++) {
            myArray[x][y] = false;
        }
    }
    
    svg.load("logo.svg");
    
    for (int i = 0; i < svg.getNumPath(); i++){
        ofPath p = svg.getPathAt(i);
        // svg defaults to non zero winding which doesn't look so good as contours
        p.setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector<ofPolyline>& lines = p.getOutline();
        for(int j=0;j<(int)lines.size();j++){
            outlines.push_back(lines[j].getResampledBySpacing(1));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    int t = ofGetElapsedTimef() * 100;
    int hue = (t * hueSpeed) % 255;
    
    color.setHsb(hue, 170, 196);
    ofSetColor(color);
    
    okToDrawSquare = true;
    
    // generate a random square
    // declare every point in the square to true (ie used)
    
    xOrigin = int(ofRandom(w));
    yOrigin = int(ofRandom(h));
    len = (ofRandom(300));
    
    // test every point in the random square to make sure it has not been used before
    for (int i = 0; i < len; i++) {
        for (int j = 0 ; j < len * ratio; j++) {
            if (myArray[xOrigin +i][yOrigin +j] == true){
                
                // Don't draw this random square
                okToDrawSquare = false;
            }
        }
    }
    
    // test to see if the square will be drawn outside the screen boundary
    if (xOrigin + len > w){
        okToDrawSquare = false;
    }
    
    if (yOrigin + len > h){
        okToDrawSquare = false;
    }
    
    // if it's OK to draw the square draw it and recored all it's points as used
    if (okToDrawSquare == true){
        ofPushMatrix();
            ofTranslate(xOrigin, yOrigin);
            ofScale(len/logoW, len/logoW);
                for (int i = 0; i < (int)outlines.size(); i++){
                    ofPolyline & line = outlines[i];
                    
                    int num = line.size();
                    
                    ofBeginShape();
                    for (int j = 0; j < num; j++){
                        ofVertex(line[j]);
                    }
                    ofEndShape();
                }
        ofPopMatrix();

        // Record all the points within the square as used
        for (int i = 0; i < len; i++) {
            for (int j = 0 ; j < len * ratio; j++) {
                myArray[xOrigin +i][yOrigin +j] = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
