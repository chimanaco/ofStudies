#include "ofApp.h"

int n_vert;

//--------------------------------------------------------------
void ofApp::setup(){
    // GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(filled.set("bFill", true));
    gui.add(zDepth.set( "zDepth", 180, 0, 400 ));
    gui.add(xNoise.set( "xNoise", 0.002, 0, 0.1 ));
    gui.add(yNoise.set( "yNoise", 0.002, 0, 0.1 ));
    
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    shader.load("vs.vert","fs.frag");
    fbo.allocate( ofGetWidth(), ofGetHeight() );
    image.loadImage("music.jpg");
//    image.resize(200, 200);
//    image.mirror(true, false);

//    mesh.setMode(OF_PRIMITIVE_POINTS);
//    
//    int w = image.getWidth();
//    int h = image.getHeight();
//    for (int x = 0; x < w; ++x) {
//        for (int y = 0; y < h; ++y) {
//            ofColor c = image.getColor(x, y);
//            ofVec3f pos(x * 4, y * 4, 0.0);
//            mesh.addVertex(pos);
//            mesh.addColor(c);
//        }
//    }
//    
//    vbo.setMesh(mesh, GL_STATIC_DRAW);
//    
//    n_vert = mesh.getNumVertices();
    
    
    
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);
    
    current_msg_string = 0;
    oscFrequency = 0;
};

float time0 = 0;
float phase = 0;
float distortAmount = 0;
float t = 0;

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
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
//    float time = ofGetElapsedTimef();
//    t = time;
};

//--------------------------------------------------------------
void ofApp::draw(){
//    ofEnableDepthTest();
//	ofBackground(33,33,33);
    
    //1. Drawing into fbo buffer
    fbo.begin();		//Start drawing into buffer
    
    //Draw something here just like it is drawn on the screen
    ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    ofSetColor( 255, 255, 255 );
    image.draw( 0, 0 );
    
    fbo.end();			//End drawing into buffer
    
    //2. Drawing to screen through the shader
    shader.begin();		//Enable the shader
    
    float time = ofGetElapsedTimef();
    shader.setUniform1f("time", time);
    shader.setUniform1f("w", ofGetWidth());
    shader.setUniform1f("h", ofGetHeight());
    
    //Draw fbo image
    ofSetColor( 255, 255, 255 );
    fbo.draw( 0, 0 );
    
    shader.end();		//Disable the shader
    
//    ofPoint p = ofPoint(-400,-400, 0);
//
//    cam.begin();
//    ofPushMatrix();
//    ofTranslate(p);
//        shader.begin();
//        shader.setUniform1f( "t", t );
//        shader.setUniform1f("freq", oscFrequency);
//        shader.setUniform1f("zDepth", zDepth);
//        shader.setUniform1f("xNoise", xNoise);
//            vbo.draw(GL_LINES, 0, n_vert);
//        shader.end();
//        ofPopMatrix();
//    cam.end();
    
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
    
//    ofDisableDepthTest();
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