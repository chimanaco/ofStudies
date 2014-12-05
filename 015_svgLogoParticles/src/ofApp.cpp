#include "ofApp.h"

float logoW = 701.977;
float logoH = 75.083;
int total = 0;
float t = 0;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(0);
	
    // load the texure
    ofDisableArbTex();
//        ofLoadImage(texture, "dot.png");
        ofLoadImage(texture, "02.jpg");
    ofEnableArbTex();
    
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(speed.set( "speed", 0.03f, 0.0001, 0.1 ));
    gui.add(numbers.set( "numbers", 1, 1, 20 ));
    gui.add(margin.set( "margin", 90, 0, 200 ));
    gui.add(hueSpeed.set( "hueSpeed", 15, 0, 30 ));
    gui.add(saturation.set( "saturation", 170, 0, 255 ));
    gui.add(brightness.set( "brightness", 196, 0, 255 ));
    gui.add(depth.set( "depth", 6000, 0, 10000 ));
    gui.add(tOff.set( "tOff", 0.15, -0.1, 0.1 ));
    gui.add(xOff.set( "xOff", 1, 0, 100 ));
    gui.add(sizeOff.set( "sizeOff", 12, 0, 100 ));


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
    
    for (int i = 0; i < (int)outlines.size(); i++){
        ofPolyline & line = outlines[i];
        int num = line.size();
        for (int j = 0; j < num; j++){
            //ofVertex(line[j]);
            points.push_back(line[j]);
//            float size = ofRandom(1, 10);
            float size = 1;
            sizes.push_back(ofVec3f(size));
        }
    }
    
    total = points.size();
    
    // why 4?
    for (int i = 0; i < total * 4; i++) {
        verticesX.push_back(ofRandom(-10, 10));
        verticesY.push_back(ofRandom(-10, 10));
        verticesZ.push_back(ofRandom(6, 10));
    }
    
    vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
    
    shader.load("of");
    vbo.setAttributeData(shader.getAttributeLocation("verticesX"),&verticesX[0],1,total,GL_STATIC_DRAW,sizeof(float));
    vbo.setAttributeData(shader.getAttributeLocation("verticesY"),&verticesY[0],1,total,GL_STATIC_DRAW,sizeof(float));
    vbo.setAttributeData(shader.getAttributeLocation("verticesZ"),&verticesZ[0],1,total,GL_STATIC_DRAW,sizeof(float));

    
}


//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    t = ofGetElapsedTimef();
    
	step += speed;
	if (step > 1) {
		step -= 1;
	}
    }

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 255, 0);

//    ofDrawBitmapString(ofToString(total),850,20);
    
    depth = 1200 * sin(t * 0.6);
    if(depth < 0) {
        depth = 0;
    }
    
    sizeOff = 80 * sin(t * 0.6);
    if(sizeOff < 20) {
        sizeOff = 20;
    }
    
    cam.begin();
    
    ofPushMatrix();
    ofScale(1, -1, 1);
    ofTranslate(-logoW / 2, -logoH / 2, 0);
    ofRotateY(40 * cos(t));
    ofRotateZ(50 * sin(t));
    
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnablePointSprites();
        shader.begin();
            shader.setUniform1f( "t", t );
            shader.setUniform1f( "depth", depth );
            shader.setUniform1f( "tOff", tOff );
            shader.setUniform1f( "sizeOff", sizeOff );
            shader.setUniform1f( "xOff", xOff );
            texture.bind();
//                vbo.draw(GL_LINES, 0, (int)points.size());
                vbo.draw(GL_POINTS, 0, (int)points.size());
            texture.unbind();
        shader.end();
    
    ofDisablePointSprites();
    ofDisableBlendMode();
	
    ofPopMatrix();
    cam.end();

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
