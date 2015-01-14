#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);

    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    
    ofEnableSmoothing();
    ofNoFill();
    ofSetColor(255, 255, 255, 200);
    
    POINTNUM = 360;
    frameCount = 0;
    t = 0;
        
    // Setup GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    gui.add(a.set( "A", 1, 0, 30 ));
    gui.add(b.set( "B", 1, 0, 30 ));
    gui.add(phiDiv.set( "PHI DIV", 4, 0.1, 5 ));
    gui.add(scaler.set( "SCALER", 100, 1, 1000 ));
    gui.add(m.set( "M", 2, 0, 30 ));
    gui.add(n1.set( "N1", 18, 0, 30 ));
    gui.add(n2.set( "N2", 1, 0, 30 ));
    gui.add(n3.set( "N3", 1, 0, 30 ));
    gui.add(duration.set( "DURATION", 300, 1, 3000 ));
    gui.add(stop.set( "STOP", 300, 1, 3000 ));
    gui.add(POINTNUM.set( "POINTNUM", 360, 3, 360 ));
    gui.add(fadeAlpha.set( "FADE ALPHA", 20, 0, 255 ));
    gui.add(lineWidth.set( "LINE WIDTH", 1, 0.1, 10 ));
    gui.add(readShader.setup("readShader"));
    
     gui.loadFromFile("settings.xml");


    
    updateShape();

    for (int i = 0; i < POINTNUM; i++) {
        float r = ofRandom(1.0);
        float g = ofRandom(1.0);
        float b = ofRandom(1.0);
//        mesh.addColor(ofFloatColor(r, g, b));
    }
    setNormals( mesh );			//Set normals to the surface

//    vbo.setVertexData(&points[0], POINTNUM, GL_STATIC_DRAW);
//    vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
    vbo.setMesh(mesh, GL_STATIC_DRAW);
    shader.load("of");
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    glLineWidth(lineWidth);
    t = ofGetElapsedTimef();
    
    if(readShader){
        shader.load("of");
    }
    
    frameCount++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0,0,0,fadeAlpha);
    ofRect(0,0,ofGetWidth(),ofGetHeight());
    
    ofFill();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    shader.begin();
        shader.setUniform1f( "t", t );
        vbo.draw(GL_LINE_LOOP, 0, POINTNUM);
    shader.end();
    
    if(frameCount > stop) {
        drawShape();
    }
    
    a = tweenA.update();
    b = tweenB.update();
    m = tweenM.update();
    n1 = tweenN1.update();
    n2 = tweenN2.update();
    n3 = tweenN3.update();
    
    updateShape();

    ofPopMatrix();
    
    // GUI
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::drawShape(){
    ofBackground(0, 0, 0);
    
    float nextA = ofRandom(0, 3);
    float nextB = ofRandom(0, 3);
    float nextM = ofRandom(0, 30);
    float nextN1 = ofRandom(0, 30);
    float nextN2 = ofRandom(0, 30);
    float nextN3 = ofRandom(0, 30);
    
    tweenA.setParameters(1,easingexpo,ofxTween::easeOut,a,nextA,duration,0);
    tweenB.setParameters(2,easingexpo,ofxTween::easeOut,b,nextB,duration,0);
    tweenM.setParameters(3,easingexpo,ofxTween::easeOut,m,nextM,duration,0);
    tweenN1.setParameters(4,easingexpo,ofxTween::easeOut,n1,nextN1,duration,0);
    tweenN2.setParameters(5,easingexpo,ofxTween::easeOut,n2,nextN2,duration,0);
    tweenN3.setParameters(6,easingexpo,ofxTween::easeOut,n3,nextN3,duration,0);
    
    frameCount = 0;
}

//--------------------------------------------------------------
void ofApp::updateShape(){
    mesh.clear();
    
    ofPoint* points = superformula(m, n1, n2, n3);
    
    for (int i = 0; i < POINTNUM; i++){
        ofVec3f v = ofVec3f(points[i].x * scaler, points[i].y * scaler, 0);
        mesh.addVertex(v);
    }
    
    setNormals( mesh );			//Set normals to the surface
    vbo.updateMesh(mesh);
}

//--------------------------------------------------------------
ofPoint ofApp::superformulaPoint(float m, float n1, float n2, float n3, float phi)
{
    float r;
    float t1,t2;
    float x = 0;
    float y = 0;
    
    t1 = cos(m * phi / phiDiv) / a;
    t1 = fabs(t1);
    t1 = pow(t1,n2);
    
    t2 = sin(m * phi / phiDiv) / b;
    t2 = fabs(t2);
    t2 = pow(t2,n3);
    
    r = pow(t1+t2,1/n1);
    if (fabs(r) == 0) {
        x = 0;
        y = 0;
    }
    else {
        r = 1 / r;
        x = r * cos(phi);
        y = r * sin(phi);
    }
    return ofPoint(x, y);
}

//--------------------------------------------------------------
ofPoint* ofApp::superformula(float m, float n1, float n2, float n3)
{
    int numPoints = POINTNUM;
    float phi = TWO_PI / numPoints;
    ofPoint* retPoints = new ofPoint[numPoints+1];
    for(int i = 0; i <= numPoints; i++){
        retPoints[i] = superformulaPoint(m, n1, n2, n3, phi * i);
    }
    return retPoints;
}

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's') {
        gui.saveToFile("settings.xml");
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