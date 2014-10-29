#include "ofApp.h"
#include "RedState.h"
#include "GreenState.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    oscFrequency = 0;
    mouseButtonState = "";
        
    // Syphon
    mainOutputSyphonServer.setName("Screen Output");
    mClient.setup();
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // setup shared data
    stateMachine.getSharedData().mainOutputSyphonServer = mainOutputSyphonServer;
    stateMachine.getSharedData().mClient = mClient;
    
    // initialise state machine
    stateMachine.addState<RedState>();
    stateMachine.addState<GreenState>();
    stateMachine.changeState("green");
}



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
        // check for mouse moved message
        if(m.getAddress() == "/FromVDMX/BPM"){
            // both the arguments are int32's
            oscBPM = m.getArgAsFloat(0);
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
    
    // shared data
    stateMachine.getSharedData().oscFrequency = oscFrequency;
    stateMachine.getSharedData().oscBPM = oscBPM;
}

//--------------------------------------------------------------
void ofApp::draw(){
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 49) {
        stateMachine.changeState("red");
    } else if (key == 50) {
        stateMachine.changeState("green");
    }
    
    // send a single string message, setting the log level
    // the legacy printf style
    ofLog(OF_LOG_NOTICE, "the number is %d", key);
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