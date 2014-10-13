#include "ofApp.h"

vector<ofPoint> vertices;
vector<ofColor> colors;
int nVert;

//--------------------------------------------------------------
void ofApp::setup(){
    // GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
	gui.add(filled.set("bFill", true));
	gui.add(angle.set( "angle", 10, -300, 300 ));
//	gui.add(center.set("center",ofVec2f(ofGetWidth()*.5,ofGetHeight()*.5),ofVec2f(0,0),ofVec2f(ofGetWidth(),ofGetHeight())));
//	gui.add(color.set("color",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
//	gui.add(circleResolution.set("circleRes", 5, 3, 90));
//	gui.add(twoCircles.setup("twoCircles"));
//	gui.add(ringButton.setup("ring"));
//	gui.add(screenSize.set("screenSize", ""));
//    
//    light.setDiffuseColor(ofFloatColor(255.0, 0.0, 0.0f));
//    light.setSpecularColor(ofColor(0, 0, 255));
//    light.setSpotlight();
//    light.setSpotConcentration(5);
//    light.setSpotlightCutOff(10);
//    light.setPosition(0, 0, 300);

    
    nVert = 1500;   // Vertices
    float Rad = 250;	//The sphere's radius
	float rad = 25;		//Maximal triangle's “radius”
	//(formally, it's the maximal coordinates'
	//deviation from the triangle's center)
    
    
    
    //Fill the vertices array
    vertices.resize( nVert );		//Set the array size

    for (int i=0; i<nVert; i++) {	//Scan all the triangles
        //Generate the center of the triangle
        //as a random point on the sphere
        
        //Take the random point from
        //cube [-1,1]x[-1,1]x[-1,1]
        ofPoint center( ofRandom( -1, 1 ),
                       ofRandom( -1, 1 ),
                       ofRandom( -1, 1 ) );
        center.normalize();		//Normalize vector's length to 1
        center *= Rad;			//Now the center vector has length Rad
        
        //Generate the triangle's vertices
        //as the center plus random point from
        //[-rad, rad]x[-rad, rad]x[-rad, rad]
       
            vertices[i] =
            center + ofPoint( ofRandom( -rad, rad ),
                             ofRandom( -rad, rad ),
                             ofRandom( -rad, rad ) );
       
    }
    
    //Fill the array of triangles' colors
    colors.resize( nVert );
    for (int i=0; i<nVert; i++) {
        //Take a random color from black to red
        colors[i] = ofColor( ofRandom( 0, 255 ), 0, 0);
    }
    
    
	//Load shader
	shader.load( "vs.vert", "fs.frag" );
    
	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	oscBeat = 0;
    oscLFOSine = 0;
	mouseButtonState = "";
}

//--------------------------------------------------------------

float time0 = 0;
float phase = 0;
float distortAmount = 0;

void ofApp::update(){
//    sync.update();

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/FromVDMX/001"){
			// both the arguments are int32's
			oscBeat = m.getArgAsFloat(0);
		}
        // check for mouse button message
		else if(m.getAddress() == "/FromVDMX/002"){
			// the single argument is a string
			oscLFOSine = m.getArgAsFloat(0);
		}
        
        else if(m.getAddress() == "/FromVDMX/Time"){
			// the single argument is a string
			oscTime = m.getArgAsFloat(0);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
//			mouseButtonState = m.getArgAsString(0);
		}
        // check for an image being sent (note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through ) 
        else if(m.getAddress() == "/image" ){
            ofBuffer buffer = m.getArgAsBlob(0);
//            receivedImage.loadImage(buffer);
        }
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

	}
    
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    
    float speed = ofMap( mouseY, 0, ofGetHeight(), 0, 5 );
    phase += speed * dt;
    distortAmount = ofMap( mouseX, 0, ofGetWidth(), 0, 1.0 );

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();				//Enable z-buffering
    
	//Set a gradient background from white to gray
	//for adding an illusion of visual depth to the scene
	ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    
	ofPushMatrix();	//Store the coordinate system
    
	//Move the coordinate center to screen's center
	ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    
	//Calculate the rotation angle
	float time = ofGetElapsedTimef();	//Get time in seconds
	float spinX = sin(time) * angle;
    float spinY = cos(time) * angle;
    ofRotate(spinX, 1.0, 0.0, 0.0);
    ofRotate(spinY, 0, 1.0, 0.0);

    ofScale(oscLFOSine + 0.5, oscLFOSine + 0.5, oscLFOSine + 0.5);
    
    //Enable the shader
	shader.begin();
	shader.setUniform1f( "phase", phase );
	shader.setUniform1f( "distortAmount", distortAmount );
    
	//Draw Sphere
	for (int i=0; i<nVert; i++) {
		ofSetColor( colors[i] );	//Set color
        ofDrawSphere(vertices[i][0], vertices[i][1], vertices[i][2], 10.0);
	}
    
    
	shader.end();	//Disable the shader

//    sphere.drawWireframe();
    
	ofPopMatrix();	//Restore the coordinate system
    
    // OSC
	string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);

	// draw mouse state
	buf = "mouse: " + ofToString(oscBeat, 4) +  " " + ofToString(mouseY, 4) +  " " + ofToString(oscLFOSine, 4);
	ofDrawBitmapString(buf, 430, 20);
	//ofDrawBitmapString(mouseButtonState, 580, 20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}
    
//    light.enable();
//    light.disable();

    
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
