#include "ofApp.h"

int n_vert;

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(33,33,33);
	//my_fbo.allocate(ofGetWidth(), ofGetHeight());

	float s = 100;
//	my_mesh.addVertex(ofVec3f(-s,s,0));
//	my_mesh.addVertex(ofVec3f(s,s,0));
//	my_mesh.addVertex(ofVec3f(s,-s,0));
//	my_mesh.addVertex(ofVec3f(-s,-s,0));
//    my_mesh = ofMesh::cylinder(100.0, 300.0);
//    my_mesh = ofMesh::icosphere(250, 2);
    my_mesh = ofMesh::plane(1500, 1500, 700, 700, OF_PRIMITIVE_TRIANGLE_STRIP);
    my_vbo.setMesh(my_mesh, GL_STATIC_DRAW);
    n_vert = my_mesh.getNumVertices();
    my_shader.load("of.vert","of.frag");
};

float time0 = 0;
float phase = 0;
float distortAmount = 0;
float t = 0;

//--------------------------------------------------------------
void ofApp::update(){
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
        if(m.getAddress() == "/FromVDMX/OneDrop"){
            // both the arguments are int32's
            oscBeat = m.getArgAsFloat(0);
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
    t = time;
};

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
	ofBackground(33,33,33);
//    ofSetLineWidth(0.5);
		cam.begin();
			my_shader.begin();
            my_shader.setUniform1f( "phase", phase );
            my_shader.setUniform1f( "distortAmount", distortAmount );
            my_shader.setUniform1f( "t", t );
            my_shader.setUniform1i("v3", oscBeat);
//            glPointSize(30.f);
//            ofSetColor(50);
//            my_vbo.drawElements(GL_TRIANGLE_STRIP, n_vert);
//            ofSetColor(150);
//            my_vbo.drawElements( GL_LINE_STRIP, n_vert * 3);
            my_vbo.draw(GL_LINES, 0, n_vert);
			my_shader.end();
		cam.end();
};

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