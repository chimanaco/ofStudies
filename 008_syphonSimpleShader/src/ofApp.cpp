#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
//    gui.add(filled.set("bFill", true));
    gui.add(number.set( "number", 8.0, 0.0, 30.0 ));
    gui.add(len.set( "len", 2.0, 0.0, 10.0 ));
    gui.add(speed.set( "speed", 5.0, 0.0, 10.0 ));

    ofBackground(0,0,0);
    my_shader.load("vs.vert","fs.frag");
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    oscFrequency = 0;
    mouseButtonState = "";
    
    mainOutputSyphonServer.setName("Screen Output");
    
    mClient.setup();
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
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
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float resolution[2];
    resolution[0] = ofGetWindowWidth();
    resolution[1] = ofGetWindowHeight();
    float time = ofGetElapsedTimef();
    
    ofEnableDepthTest();

    my_shader.begin();
    my_shader.setUniform1f("time", time);
    my_shader.setUniform1f("number", number);
    my_shader.setUniform1f("len", len);
    my_shader.setUniform1f("speed", speed);
    my_shader.setUniform2fv("resolution", resolution);
    
    
    //my_vbo.draw(GL_LINES, 0, n_vert);
    
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(ofGetWidth(), 0);
    glVertex2f(ofGetWidth(), ofGetHeight());
    glVertex2f(0, ofGetHeight());
    glEnd();

    my_shader.end();
    
    // Syphon Stuff
    
    mClient.draw(50, 50);
    
    mainOutputSyphonServer.publishScreen();
    
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