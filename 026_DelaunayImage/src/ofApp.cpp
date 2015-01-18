#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofBackground(0);

	frameCount = 0;
	total = 0;
	margin = 10;

	gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(ratio.set( "IMG RATIO", 1.5, 1, 10 ));
	gui.add(maxCount.set( "MAX COUNT", 30000, 3000, 60000 ));
	gui.add(size.set( "MINIMUM SIZE", 3, 1, 30 ));
    gui.add(shapes.set( "SHAPE", 0, 0, 2 ));

	img.loadImage("images/fn.jpg");
	//img.loadImage("images/beer.jpg");
	img.resize(img.width / ratio, img.height / ratio);
	img.setImageType(OF_IMAGE_COLOR);

	w = img.getWidth();
	h = img.getHeight();

	initDelaunay();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
	frameCount++;
}

//--------------------------------------------------------------
void ofApp::draw(){
	// original image
	ofSetColor(255);

	ofPushMatrix();
		ofTranslate(0, h / 2);
			img.draw(0, 0, 0, w, h);
	ofPopMatrix();

	// delaunay
	if(frameCount < maxCount) {
		float x = ofRandom(w);
		float y = ofRandom(h);

		ofColor imgColor = img.getColor(x, y);
		if(imgColor.getBrightness() < 253) {
			ofVec2f p = ofVec2f(x, y);
			// collision detection / return true if no collision
			if(sample(p)) {
				particles.push_back(p);
				del.addPoint(ofPoint(p.x,p.y));
				del.triangulate();
			}
		}
	}

	// Mesh
	mesh.clear();
	total = del.triangleMesh.getNumIndices();

	for(int j = 0; j < total / 3; j++) {
		int indx1 = del.triangleMesh.getIndex(j*3);
		ofVec3f p1 = del.triangleMesh.getVertex(indx1);
		int indx2 = del.triangleMesh.getIndex(j*3+1);
		ofVec3f p2 = del.triangleMesh.getVertex(indx2);
		int indx3 = del.triangleMesh.getIndex(j*3+2);
		ofVec3f p3 = del.triangleMesh.getVertex(indx3);

		ofVec3f triangleCenter = (p1+p2+p3)/3.0;
		ofColor newColor = img.getColor(triangleCenter.x, triangleCenter.y);

		mesh.addVertex(p1);
		//mesh.addColor(del.triangleMesh.getColor(indx1));
		mesh.addColor(newColor);

		mesh.addVertex(p2);
		mesh.addColor(newColor);

		mesh.addVertex(p3);
		mesh.addColor(newColor);
	}
	
	if(shapes == 1) {
		ofNoFill();
	}

	if(shapes == 2) {
		glPointSize(size);
	}
	
	vbo.setMesh(mesh, GL_STATIC_DRAW);    
	ofPushMatrix();
		ofTranslate(w + margin, h / 2);
			if(shapes == 0) {
				vbo.draw(GL_TRIANGLES, 0, total);
			} else if(shapes == 1) {
				vbo.draw(GL_LINES, 0, total);
			} else {
				vbo.draw(GL_POINTS, 0, total);
			}				
			
	ofPopMatrix();
	
    //ofNoFill();
	//ofSetColor(255, 255, 255);
    //del.draw();

	ofDrawBitmapString(ofToString(frameCount) + " / " + ofToString(maxCount) , ofPoint(w + margin,20));
	ofDrawBitmapString("NumIndices: " + ofToString(total) , ofPoint(w + margin,40));

	gui.draw();
}

//--------------------------------------------------------------
void ofApp::initDelaunay(){
    del.addPoint(ofPoint(0, 0));
	del.addPoint(ofPoint(0, h));
	del.addPoint(ofPoint(w, h));
	del.addPoint(ofPoint(w, 0));
}

//--------------------------------------------------------------
bool ofApp::sample(ofVec2f p){
	for (int i = 0; i < particles.size(); i++)	{
		float c1 = pow(double(p.x) - particles[i].x, 2);
		float c2 = pow(double(p.y) - particles[i].y, 2);
		float s1 = pow(double(size * 2), 2);

		if( c1 + c2 < s1) {
			return false;
		}
	}

	return true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r'){
        del.reset();
		initDelaunay();
		frameCount = 0;
    }
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
    //del.addPoint(ofPoint(x,y));
    //del.triangulate();
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