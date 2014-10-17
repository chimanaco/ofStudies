#include "ofApp.h"

int n_vert;

//--------------------------------------------------------------
void ofApp::setup(){
    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
    
    // GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(filled.set("bFill", true));
    gui.add(zDepth.set( "zDepth", 200, 0, 400 ));
    //gui.add(vs.set( "vs", 30, 1, 1000 ));
    //gui.add(circleResolution.set( "circleResolution", 10, 1, 1000 ));
    gui.add(circleResolution.set( "circleResolution", 50, 1, 1000 ));
    //gui.add(vertical.set( "vertical", 30, 1, 1000 ));
    
    
	ofBackground(33,33,33);
	//my_mesh = ofMesh::plane(1500, 1500, 1500, 1500, OF_PRIMITIVE_TRIANGLE_STRIP);
    //my_mesh = ofMesh::plane(1000, 1000, 1000, 200, OF_PRIMITIVE_TRIANGLE_STRIP);
    //my_mesh = ofMesh::plane(1000, 1000, 2000, 1000, OF_PRIMITIVE_TRIANGLE_STRIP);
    my_shader.load("of.vert","of.frag");
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    oscFrequency = 0;
    mouseButtonState = "";
};

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
    // these should be in setup() normally
    if(circleResolution % 2 == 1) {
        circleResolution++;
    }
    
    my_mesh = ofMesh::plane(1500, 1500, circleResolution, 500, OF_PRIMITIVE_TRIANGLE_STRIP);
    my_vbo.setMesh(my_mesh, GL_STATIC_DRAW);
    n_vert = my_mesh.getNumVertices();
}

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
        if(m.getAddress() == "/FromVDMX/Frequency"){
            // both the arguments are int32's
            oscFrequency = m.getArgAsFloat(0);
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
    t = time;
};

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
	ofBackground(33,33,33);
//    ofSetLineWidth(0.5;)

		cam.begin();
			my_shader.begin();
            my_shader.setUniform1f( "t", t );
            my_shader.setUniform1f("freq", oscFrequency);
            my_shader.setUniform1f("zDepth", zDepth);
//            glPointSize(30.f);
//            ofSetColor(50);
//            my_vbo.drawElements(GL_TRIANGLE_STRIP, n_vert);
//            ofSetColor(150);
//            my_vbo.drawElements( GL_LINE_STRIP, n_vert * 3);
            my_vbo.draw(GL_LINES, 0, n_vert);
			my_shader.end();
		cam.end();
    
    // OSC
    string buf;
    buf = "listening for osc messages on port" + ofToString(PORT);
    ofDrawBitmapString(buf, 10, 20);
    
    // draw mouse state
    buf = "mouse: " + ofToString(oscFrequency, 4) +  " " + ofToString(mouseY, 4);
    ofDrawBitmapString(buf, 430, 20);
    //ofDrawBitmapString(mouseButtonState, 580, 20);
    
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
    }
    
    //    light.enable();
    //    light.disable();
    
    
    ofDisableDepthTest();
    gui.draw();
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