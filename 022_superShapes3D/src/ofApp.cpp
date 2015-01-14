#include "ofApp.h"

int shapeTotal = 19;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // GL_REPEAT for texture wrap only works with NON-ARB textures //
    ofDisableArbTex();
    texture.loadImage("ConcreteBare0055_5_thumbhuge.jpg"); // texture: http://www.
    texture.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    ofEnableArbTex();
    
    shaderNumber.addListener(this, &ofApp::shaderNumberChanged);
    
    gui.setup("panel");
    gui.add(radius.set("RADIUS", 100, 1, 300));
    gui.add(a1.set( "a1", 1, 0, 5 ));
    gui.add(b1.set( "b1", 1, 0, 5 ));
    gui.add(m1.set( "m1", 5, 0, 20 ));
    gui.add(n11.set( "n11", 1, 0, 100 ));
    gui.add(n21.set( "n21", 1, -50, 100 ));
    gui.add(n31.set( "n31", 2, -50, 100 ));
    gui.add(a2.set( "a2", 1, 0, 5 ));
    gui.add(b2.set( "b2", 1, 0, 5 ));
    gui.add(m2.set( "m2", 5, 0, 20 ));
    gui.add(n12.set( "n12", 1, 0, 100 ));
    gui.add(n22.set( "n22", 1, -50, 100 ));
    gui.add(n32.set( "n32", 3, -50, 100 ));
    gui.add(alpha.set( "alpha", 1, 0.01, 5 ));
    gui.add(beta.set( "beta", 4, 0.01, 10 ));
    gui.add(lightX.set( "lightX", 0, -2000, 2000 ));
    gui.add(lightY.set( "lightY", 0, -2000, 2000 ));
    gui.add(lightZ.set( "lightZ", 0, -2000, 2000 ));
    gui.add(drawType.set( "DRAW TYPE", 0, 0, 3 ));
    gui.add(pointSize.set( "POINT SIZE", 3, 1, 10 ));
    gui.add(rotation.set( "ROTATION ON", false ));
    gui.add(bShader.set( "SHADER ON", false ));
    gui.add(shaderNumber.set( "SHADER", 0, 0, 3 ));
    gui.add(duration.set( "DURATION", 300, 1, 3000 ));
    gui.add(stop.set( "STOP", 300, 1, 3000 ));
    gui.add(shapeNumber.set( "SHAPE", 0, 0, shapeTotal ));
    gui.add(bChanger.set( "CHANGER ON", false ));
    gui.loadFromFile("settings.xml");
    
    // emerald
    material.setShininess(76.8);
    material.setAmbientColor(ofColor(5.4825, 44.4975, 5.4825, 255));
    material.setDiffuseColor(ofColor(19.2984, 156.6312, 19.2984, 255));
    material.setSpecularColor(ofColor(161.415, 185.591805, 161.415, 255));
    color.set(ofColor(19.2984, 156.6312, 19.2984));

    // turquoise
//    material.setShininess(25.5);
//    material.setAmbientColor(ofColor(25.5, 47.74875, 44.4975, 255));
//    material.setDiffuseColor(ofColor(100.98, 189.08505, 176.2101, 255));
//    material.setSpecularColor(ofColor(75.79977, 78.61395, 78.20289, 255));
//    color.set(ofColor(100.98, 189.08505, 176.2101));
    
    // Red Plastic
//    material.setShininess(63.75);
//    material.setAmbientColor(ofColor(0, 0, 0, 255));
//    material.setDiffuseColor(ofColor(127.5, 0, 0, 255));
//    material.setSpecularColor(ofColor(178.5, 153, 153, 255));
//    color.set(ofColor(127.5, 0, 0, 255));

//    // Ruby
//    material.setShininess(153);
//    material.setAmbientColor(ofColor(44.4975, 2.99625, 2.99625, 255));
//    material.setDiffuseColor(ofColor(156.6312, 10.5468, 10.5468, 255));
//    material.setSpecularColor(ofColor(185.591805, 159.874545, 159.874545, 255));
//    color.set(ofColor(156.6312, 10.5468, 10.5468, 255));
    
    // chrome
//    material.setShininess(76.8);
//    material.setAmbientColor(ofColor(63.75, 63.75, 63.75, 255));
//    material.setDiffuseColor(ofColor(102, 102, 102, 255));
//    material.setSpecularColor(ofColor(197.522235, 197.522235, 197.522235, 255));
//    color.set(ofColor(63.75, 63.75, 63.75));    //chrome

//
//    // white rubber
//    material.setShininess(19.921875);
//    material.setAmbientColor(ofColor(12.75, 12.75, 12.75, 255));
//    material.setDiffuseColor(ofColor(12.75, 12.75, 12.75, 255));
//    material.setSpecularColor(ofColor(178.5, 178.5, 178.5, 255));
//    color.set(ofColor(178.5, 178.5, 178.5, 255));    //white rubber

    
    // Gold
//    material.setShininess(102);
//    material.setAmbientColor(ofColor(55.63125, 50.8725, 18.9975, 255));
//    material.setDiffuseColor(ofColor(191.6682, 154.6524, 57.7524, 255));
//    material.setSpecularColor(ofColor(160.211655, 141.72951, 93.346575, 255));
//    color.set(ofColor(191.6682, 154.6524, 57.7524));    //Gold

      // red rubber
//    material.setShininess(19.921875);
//    material.setAmbientColor(ofColor(12.75, 0, 0, 255));
//    material.setDiffuseColor(ofColor(122.75, 102, 102, 255));
//    material.setSpecularColor(ofColor(178.5, 10.2, 10.2, 255));
//    color.set(ofColor(122.75, 102, 102, 255));    //white rubber

    
//    red rubber	0.05	0.0	0.0	0.5	0.4	0.4	0.7	0.04	0.04	.078125
    
    
    ofSetColor(color);
    
    // mesh, vbo
    mesh.setMode(OF_PRIMITIVE_POINTS);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    et = ofGetElapsedTimef();

    if(rotation) {
        angle += 0.5;
    }

    glPointSize(pointSize);
    
    if(bChanger) {
        radius = tweenRadius.update();
        a1 = tweenA1.update();
        b1 = tweenB1.update();
        m1 = tweenM1.update();
        n11 = tweenN11.update();
        n21 = tweenN21.update();
        n31 = tweenN31.update();
        a2 = tweenA2.update();
        b2 = tweenB2.update();
        m2 = tweenM2.update();
        n12 = tweenN12.update();
        n22 = tweenN22.update();
        n32 = tweenN32.update();
        alpha = tweenAlpha.update();
        beta = tweenBeta.update();
    }
    
    if(frameCount > stop) {
        updateShape();
    }
    
    frameCount++;
    
    objectUpdate();
}



//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    ofBackgroundGradient( ofColor( 255 ), ofColor( 0 ) );
    
    light.enable();
    light.setPosition(lightX, lightY, lightY);
    
    cam.begin();
        material.begin();
                texture.getTextureReference().bind();
            if(bShader) {
                shader.begin();
                shader.setUniform1f( "t", et );
            }
    
			ofPushMatrix();
				ofRotate(angle, 1, 0, 0);

                if(drawType == 0) {
                    vbo.drawElements(GL_QUADS, total * 6);	// why 6?
                } else if(drawType == 1) {
                    vbo.drawElements(GL_QUAD_STRIP, total * 6);	// why 6?
                } else if(drawType == 2) {
                    vbo.drawElements(GL_LINE_LOOP, total * 6);	// why 6?
                } else if(drawType == 3) {
                    vbo.drawElements(GL_POINTS, total * 6);	// why 6?
                }
			ofPopMatrix();
    
            if(bShader) {
                shader.end();
            }
        	texture.getTextureReference().unbind();
        material.end();
    cam.end();
    
    ofDisableLighting();
    
    // GUI
    ofDisableDepthTest(); // for 3D
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::objectUpdate(){
    // clear
    mesh.clear();
    
    step = 0.05;
    int q = (int)(4 * PI / step + 1.3462);
    int o = (int)(PI / step + 1.5);
    for (int l = 0; l < (q); l++) {
        float u = -PI + l * step;
        for (int h = 0; h < (o); h++) {
            float s = -PI / 2 + h * step;
            float m, k, n, g, v, e, t;
            float f = 0;
            float p = 0;
            float w = 0;
            m = cos(m1 * u / beta);
            m = alpha / a1 * abs(m);
            m = abs(m);
            k = sin(m1 * u / beta);
            k = alpha / b1 * abs(k);
            k = abs(k);
            g = pow(m, n21) + pow(k, n31);
            v = abs(g);
            v = pow(v, (-alpha / n11));
            m = cos(m2 * s / beta);
            m = alpha / a2 * abs(m);
            m = abs(m);
            k = sin(m2 * s / beta);
            k = alpha / b2 * abs(k);
            k = abs(k);
            e = pow(m, n22) + pow(k, n32);
            t = abs(e);
            t = pow(t, (-alpha / n12));
            f = v * cos(u) * t * cos(s) * radius;
            p = v * sin(u) * t * cos(s) * radius;
            w = t * sin(s) * radius;
            ofVec3f pos(f, p, w);
            mesh.addVertex(pos);
            mesh.addTexCoord(pos);

//            ofFloatColor color;
//            color.setHsb(ofNoise(et * 0.3,h * 0.01),0.8, 0.8);
//            mesh.addColor(color);

        }
    }
    
    for (int u = 0; u < (q - 1); u++) {
        for (int s = 0; s < (o - 1); s++) {
            int d = u * o + s;
            int c = u * o + s + 1;
            int b = (u + 1) * o + s + 1;
            int a = (u + 1) * o + s;
            
            mesh.addIndex(d);
            mesh.addIndex(c);
            mesh.addIndex(b);
            mesh.addIndex(a);
        }
    }
    
    setNormals( mesh );			//Set normals to the surface
    //Note, setNormals is our function,
    //which is declared

    vbo.setMesh(mesh, GL_STATIC_DRAW);
    total = mesh.getNumVertices();
}

//--------------------------------------------------------------
void ofApp::updateShape(){
    if(!bChanger) return;
    
    shapeNumber = (int) ofRandom(shapeTotal+1);
//    shapeNumber = 0;
    
    ofxXmlSettings panel;
    panel.loadFile("shape" + ofToString(shapeNumber) +".xml");
    
    float nextRadius = panel.getValue("panel:radius", 0.0);
    float nextA1 = panel.getValue("panel:a1", 0.0);
    float nextB1 = panel.getValue("panel:b1", 0.0);
    float nextM1 = panel.getValue("panel:m1", 0.0);
    float nextN11 = panel.getValue("panel:n11", 0.0);
    float nextN21 = panel.getValue("panel:n21", 0.0);
    float nextN31 = panel.getValue("panel:n31", 0.0);
    float nextA2 = panel.getValue("panel:a2", 0.0);
    float nextB2 = panel.getValue("panel:b2", 0.0);
    float nextM2 = panel.getValue("panel:m2", 0.0);
    float nextN12 = panel.getValue("panel:n12", 0.0);
    float nextN22 = panel.getValue("panel:n22", 0.0);
    float nextN32 = panel.getValue("panel:n32", 0.0);
    float nextAlpha = panel.getValue("panel:alpha", 0.0);
    float nextBeta = panel.getValue("panel:beta", 0.0);
   
//    bShader = (int) ofRandom(2);
//    
//    if(bShader) {
//        drawType = (int) ofRandom(3);
//    } else {
//        drawType = (int) ofRandom(4);
//    }
//    
//    pointSize = (int) ofRandom(5);
    
//    bShader = panel.getValue("panel:SHADER_ON", 0.0);
//    shaderNumber = panel.getValue("panel:SHADER", 0.0);
//    drawType = panel.getValue("panel:DRAW_TYPE", 0.0);
//    pointSize = panel.getValue("panel:POINT_SIZE", 0.0);
    
    tweenRadius.setParameters(0,easingexpo,ofxTween::easeOut,radius,nextRadius,duration,0);
    tweenA1.setParameters(1,easingexpo,ofxTween::easeOut,a1,nextA1,duration,0);
    tweenB1.setParameters(2,easingexpo,ofxTween::easeOut,b1,nextB1,duration,0);
    tweenM1.setParameters(3,easingexpo,ofxTween::easeOut,m1,nextM1,duration,0);
    tweenN11.setParameters(4,easingexpo,ofxTween::easeOut,n11,nextN11,duration,0);
    tweenN21.setParameters(5,easingexpo,ofxTween::easeOut,n21,nextN21,duration,0);
    tweenN31.setParameters(6,easingexpo,ofxTween::easeOut,n31,nextN31,duration,0);
    tweenA2.setParameters(7,easingexpo,ofxTween::easeOut,a2,nextA2,duration,0);
    tweenB2.setParameters(8,easingexpo,ofxTween::easeOut,b2,nextB2,duration,0);
    tweenM2.setParameters(9,easingexpo,ofxTween::easeOut,m2,nextM2,duration,0);
    tweenN12.setParameters(10,easingexpo,ofxTween::easeOut,n12,nextN12,duration,0);
    tweenN22.setParameters(11,easingexpo,ofxTween::easeOut,n22,nextN22,duration,0);
    tweenN32.setParameters(12,easingexpo,ofxTween::easeOut,n32,nextN32,duration,0);
    tweenAlpha.setParameters(13,easingexpo,ofxTween::easeOut,alpha,nextAlpha,duration,0);
    tweenBeta.setParameters(14,easingexpo,ofxTween::easeOut,beta,nextBeta,duration,0);
    
    frameCount = 0;
}

//--------------------------------------------------------------
void ofApp::shaderNumberChanged(int & shaderNumber){
    shader.load("shader" + ofToString(shaderNumber) +"/of");
}

//--------------------------------------------------------------

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
void ofApp::exit()
{
    gui.saveToFile("settings.xml");
}

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