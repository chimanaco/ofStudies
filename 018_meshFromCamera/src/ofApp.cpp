/**
 *
 * OFDevCon Example Code Sprint
 * 
 * This example shows building a mesh, texturing it with a webcam, and extruding the vertices based on the pixel brightness
 * Moving the mouse also rotates the mesh to see it at different angles
 *
 * Created by Tim Gfrerer and James George for openFrameworks workshop at Waves Festival Vienna sponsored by Lichterloh and Pratersauna
 * Adapted during ofDevCon on 2/23/2012
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(0,0,0);
    
	//initialize the video grabber
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
//    vidGrabber.initGrabber(640,480);

	//store the width and height for convenience
	int width = vidGrabber.getWidth();
	int height = vidGrabber.getHeight();
	
	//add one vertex to the mesh for each pixel
	for (int y = 0; y < height; y++){
		for (int x = 0; x<width; x++){
			mainMesh.addVertex(ofPoint(x,y,0));	// mesh index = x + y*width
												// this replicates the pixel array within the camera bitmap...
			mainMesh.addColor(ofFloatColor(0,0,0));  // placeholder for colour data, we'll get this from the camera
		}
	}
	
	for (int y = 0; y<height-1; y++){
		for (int x=0; x<width-1; x++){
			mainMesh.addIndex(x+y*width);				// 0
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex(x+(y+1)*width);			// 10
			
			mainMesh.addIndex((x+1)+y*width);			// 1
			mainMesh.addIndex((x+1)+(y+1)*width);		// 11
			mainMesh.addIndex(x+(y+1)*width);			// 10
		}
	}
    
	//this is an annoying thing that is used to flip the camera
//	cam.setScale(1,-1,1);
	
	
	//this determines how much we push the meshes out
//	extrusionAmount = 300.0;
    
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(false);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    //post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<SSAOPass>()->setEnabled(false);
    post.createPass<ToonPass>()->setEnabled(false);

}

//--------------------------------------------------------------
void ofApp::update(){
    float t = ofGetElapsedTimef();
//    extrusionAmount = 200 * ofNoise(t, 0.1) + 300;
    extrusionAmount = 300;
    
	//grab a new frame
	vidGrabber.update();
	
	//update the mesh if we have a new frame
	if (vidGrabber.isFrameNew()){
		//this determines how far we extrude the mesh
		for (int i=0; i<vidGrabber.getWidth()*vidGrabber.getHeight(); i++){

			ofFloatColor sampleColor(vidGrabber.getPixels()[i*3]/255.f,				// r
									 vidGrabber.getPixels()[i*3+1]/255.f,			// g
									 vidGrabber.getPixels()[i*3+2]/255.f);			// b
			
			//now we get the vertex aat this position
			//we extrude the mesh based on it's brightness
			ofVec3f tmpVec = mainMesh.getVertex(i);
			tmpVec.z = sampleColor.getBrightness() * (100 * ofNoise(i+t, 0.1) + 300);
			mainMesh.setVertex(i, tmpVec);

			mainMesh.setColor(i, sampleColor);
		}
	}
    
	//let's move the camera when you move the mouse
	float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);

	
	//move the camera around the mesh
	ofVec3f camDirection(0,0,1);
	ofVec3f centre(vidGrabber.getWidth()/2.f,vidGrabber.getHeight()/2.f, 255/2.f);
	ofVec3f camDirectionRotated = camDirection.rotated(rotateAmount, ofVec3f(1,0,0));
	ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
	
	cam.setPosition(camPosition);
	cam.lookAt(centre);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//we have to disable depth testing to draw the video frame
	ofDisableDepthTest();
//	vidGrabber.draw(20,20);
	
	//but we want to enable it to show the mesh
	ofEnableDepthTest();
    post.begin();
        cam.begin();

            ofEnableBlendMode(OF_BLENDMODE_ADD);
        //    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
            //You can either draw the mesh or the wireframe
        	 mainMesh.drawWireframe();
//            mainMesh.drawFaces();
        //    mainMesh.draw();
//            mainMesh.drawVertices();

            ofDisableBlendMode();
        
        cam.end();
    post.end();
	
	//draw framerate for fun
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
	
    /*// draw help postprocessing
    ofSetColor(0, 255, 255);
    ofDrawBitmapString("Number keys toggle effects, mouse rotates scene", 10, 500);
    for (unsigned i = 0; i < post.size(); ++i)
    {
        if (post[i]->getEnabled()) ofSetColor(0, 255, 255);
        else ofSetColor(255, 0, 0);
        ostringstream oss;
        oss << i << ": " << post[i]->getName() << (post[i]->getEnabled()?" (on)":" (off)");
        ofDrawBitmapString(oss.str(), 10, 20 * (i + 2) + 500);
    }*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case 'f':
			ofToggleFullscreen();
			break;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //toggle between normalized and not to get a sense of the effects
    //You will need to set a volume range if you're not normalizing everything - but this will depend on your sound source and input type to determine the maximum volume range of your codez
    
    //    if(key=='q'){
    //        fft.setVolumeRange(100);
    //        fft.setNormalize(false);
    //    }
    //    if(key=='r'){
    //        fft.setNormalize(true);
    //    }
    
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
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
