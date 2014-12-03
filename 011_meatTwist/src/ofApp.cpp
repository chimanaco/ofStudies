#include "ofApp.h"

int NUM = 100;
ofBoxPrimitive boxes[100];

float w = 200;
float h = 40;
float d = 80;
float hMargin = 1.1;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(speed.set( "speed", 200, 10, 300 ));
    gui.add(cameraXRadius.set( "cameraXRadius", 150, 0, 5000 ));
    gui.add(cameraZRadius.set( "cameraZRadius", 1000, 0, 5000 ));
    
    // GL_REPEAT for texture wrap only works with NON-ARB textures //
    ofDisableArbTex();
    texture.loadImage("Meat0016_thumbhuge.jpg"); // texture: http://www.cgtextures.com/
    texture.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    ofEnableArbTex();
    
    for (int i = 0; i < NUM; i++)
    {
        boxes[i].set( w, h, d );
        boxes[i].setPosition(0, (h * hMargin) * i - (h * hMargin) * NUM / 2, 0);
    }
    
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    
    pointLight2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    pointLight2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));
    
    pointLight3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    pointLight3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
    material.setShininess( 120 );
    // the light highlight of the material //
    material.setSpecularColor(ofColor(255, 255, 255, 255));
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    pointLight2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                            ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    pointLight3.setPosition(
                            cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                            sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                            cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                            );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(30, 0);
    float t = ofGetElapsedTimef();
    //bg.draw(0, 0);
    
    cam.begin();
    cam.setPosition(ofVec3f(cameraXRadius * cos(t * 0.1f), 300, cameraZRadius * sin(t * 0.1f)));
    //cam.setPosition(ofVec3f(0, 300, 1000));
    cam.lookAt(ofVec3f(0, 0, 0));
    
    ofEnableDepthTest();
    ofEnableLighting();
    
    pointLight.enable();
    pointLight2.enable();
    pointLight3.enable();
    
    material.begin();
    texture.getTextureReference().bind();
				
				ofPushMatrix();
				//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
				ofRotateZ(t * 10.0f);
				
				// Box
				for (int i = 0; i < NUM; i++)
                {
                    ofPushMatrix();
                    //ofScale(cos(t * 0.01) * i / NUM * 5, 1.0, 1.0);
                    //ofScale(cos( (t + i) * 0.8) * 3.0, 1.0, 1.0);
                    
                    //float spinX = sin(ofGetElapsedTimef()*.35f)*i;
                    //float spinY = cos(ofGetElapsedTimef()*.075f)*(i+1);
                    //float spinY = (t + i) *5.075f;
                    //float spinY = sin( (t + i * 0.3) * 0.001f ) * speed;
                    float spinY = i * 0.001f * speed;
                    boxes[i].rotate(spinY, 0, 1.0, 0.0);
                    //boxes[i].rotate(i/NUM*360,0,1.0,0.0);
                    boxes[i].draw();
                    ofPopMatrix();
                }
    
				ofPopMatrix();
    material.end();
    
    ofDisableLighting();
    
    ofDisableDepthTest();
    cam.end();
    // gui
    gui.draw();
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
