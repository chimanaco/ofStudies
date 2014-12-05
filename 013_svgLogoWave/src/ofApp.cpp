#include "ofApp.h"

float logoW = 701.977;
float logoH = 75.083;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(0);
	ofSetColor(255);
	
    center = ofVec3f(0, 0, 0);
    
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(speed.set( "speed", 0.03f, 0.0001, 0.1 ));
    gui.add(numbers.set( "numbers", 30, 1, 30 ));
    gui.add(scale.set( "scale", 0.06, 0, 1 ));
    gui.add(margin.set( "margin", 19, 0, 50 ));
    gui.add(hueSpeed.set( "hueSpeed", 6, 0, 30 ));
    gui.add(saturation.set( "saturation", 170, 0, 255 ));
    gui.add(brightness.set( "brightness", 196, 0, 255 ));
    gui.add(camX.set( "camX", -30, -3000, 3000 ));
    gui.add(camY.set( "camY", 90, -3000, 3000 ));
    gui.add(camZ.set( "camZ", 700, -700, 700 ));

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
    
    ofEnableDepthTest();
    
    cam.begin();
    cam.setPosition(ofVec3f(sin(t * 0.003) * 300, camY, sin(t * 0.003) * 700 ) );
    cam.lookAt(center);
    
    //ofNoFill();
    ofFill();
    
    for (int i = 0; i < (int)outlines.size(); i++){
        ofPolyline & line = outlines[i];

        //int num = step * line.size();
        int num = line.size();
        
        for (int j = 0; j < numbers; j++) {
            int hue = (t + (i + j) * hueSpeed) % 255;
            color.setHsb(hue, saturation, brightness);
            ofSetColor(color);
            
            ofPushMatrix();
                ofScale(1, -1, 1);
            
                ofTranslate(-logoW * scale * (j+1) / 2, -logoH * scale * (j+1) / 2 + ofNoise(t * 0.003, j * 0.1) * -1000 + 500, margin * j - 500);
                ofScale(scale * j, scale * j, scale * j);

                ofBeginShape();
                    for (int j = 0; j < num; j++){
                        ofVertex(line[j]);
                        //                            ofCircle(line[j], radius);
                    }
                ofEndShape();
            ofPopMatrix();
        }
    }
    
    cam.end();
    
    // GUI
    ofDisableDepthTest();
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
