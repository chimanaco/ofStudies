#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    
    ofEnableSmoothing();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    
    frameCount = 0;
    
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(speed.set( "SPEED", 5, 1, 60 ));
    gui.add(sNumber.set( "S", 2, 1, 60 ));
    gui.add(newScalarOffset.set( "OFFSET", 0.98, 0, 4 ));
    gui.add(a.set( "A", 1, 0, 30 ));
    gui.add(b.set( "B", 1, 0, 30 ));
    gui.add(phiDiv.set( "PHI DIV", 4, 0.1, 5 ));
    gui.add(scaler.set( "SCALER", 20, 1, 6000 ));
    gui.add(m.set( "M", 2, 0, 30 ));
    gui.add(n1.set( "N1", 18, 0, 30 ));
    gui.add(n2.set( "N2", 1, 0, 30 ));
    gui.add(n3.set( "N3", 1, 0, 30 ));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    frameCount++;
    if(frameCount > 120) {
        updateFormula();
    }
    
    scaler += speed;

    float newscaler = scaler;
    for(int s = sNumber; s > 0; s--){
        ofBeginShape();
        
        float mm = m + s;
        float nn1 = n1 + s;
        float nn2 = n2 + s;
        float nn3 = n3 + s;
        newscaler = newscaler * newScalarOffset;
        float sscaler = newscaler;
        
        ofPoint* points = superformula(mm, nn1, nn2, nn3);
        ofCurveVertex(points[POINTNUM-1].x * sscaler, points[POINTNUM-1].y * sscaler);
        for(int j = 0; j < POINTNUM; j++){
            ofCurveVertex(points[j].x * sscaler, points[j].y * sscaler);
//            ofFill();
//            ofCircle(points[j].x * sscaler, points[j].y * sscaler, 2);
        }
        ofCurveVertex(points[0].x * sscaler, points[0].y * sscaler);
        
        
        ofEndShape(true);
    }
    ofPopMatrix();
    
    // GUI
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::updateFormula(){
    a = ofRandom(0, 3);
    b = ofRandom(0, 3);
    sNumber = ofRandom(1, 20);
    newScalarOffset = ofRandom(0, 2);
    scaler = ofRandom(0, 200);
    m = ofRandom(0, 30);
    n1 = ofRandom(0, 30);
    n2 = ofRandom(0, 30);
    n3 = ofRandom(0, 30);
    frameCount = 0;
}

//--------------------------------------------------------------
ofPoint ofApp::superformulaPoint(float m, float n1, float n2, float n3, float phi)
{
    float r;
    float t1,t2;
    float x = 0;
    float y = 0;
    
    t1 = cos(m * phi / phiDiv) / a;
    t1 = fabs(t1);
    t1 = pow(t1,n2);
    
    t2 = sin(m * phi / phiDiv) / b;
    t2 = fabs(t2);
    t2 = pow(t2,n3);
    
    r = pow(t1+t2,1/n1);
    if (fabs(r) == 0) {
        x = 0;
        y = 0;
    }
    else {
        r = 1 / r;
        x = r * cos(phi);
        y = r * sin(phi);
    }
    return ofPoint(x, y);
}

//--------------------------------------------------------------
ofPoint* ofApp::superformula(float m, float n1, float n2, float n3)
{
    int numPoints = POINTNUM;
    float phi = TWO_PI / numPoints;
    ofPoint* retPoints = new ofPoint[numPoints+1];
    for(int i = 0; i <= numPoints; i++){
        retPoints[i] = superformulaPoint(m, n1, n2, n3, phi * i);
    }
    return retPoints;
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