#include "ofApp.h"

float logoW = 701.977;
float logoH = 75.083;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(0);
	ofSetColor(255);
	
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(speed.set( "speed", 0.03f, 0.0001, 0.1 ));
    gui.add(numbers.set( "numbers", 1, 1, 20 ));
    gui.add(margin.set( "margin", 90, 0, 200 ));
    gui.add(hueSpeed.set( "hueSpeed", 15, 0, 30 ));
    gui.add(saturation.set( "saturation", 170, 0, 255 ));
    gui.add(brightness.set( "brightness", 196, 0, 255 ));


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

	step += speed;
	if (step > 1) {
		step -= 1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    int t = ofGetElapsedTimef() * 100;
    
    ofPushMatrix();
//	ofTranslate(ofGetWidth() / 2 - logoW / 2, logoH / 2);
    ofTranslate(ofGetWidth() / 2 - logoW / 2, ofGetHeight() / 2 - logoH / 2 * numbers);
    
    ofNoFill();
    ofFill();
    
    for (int i = 0; i < (int)outlines.size(); i++){
        ofPolyline & line = outlines[i];

        int num = step * line.size();
        
        for (int j = 0; j < numbers; j++) {
            int hue = (t + (i + j) * hueSpeed) % 255;
            color.setHsb(hue, saturation, brightness);
            ofSetColor(color);
            
            ofPushMatrix();
                ofTranslate(0, j * margin);
                    ofBeginShape();
                        for (int j = 0; j < num; j++){
                            ofVertex(line[j]);
                        }
                    ofEndShape();
            ofPopMatrix();
        }
    }
	
	ofPopMatrix();
    
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
