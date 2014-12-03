/*
 *  RedState.cpp
 *
 *  Copyright (c) 2011, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of 16b.it nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "RedState.h"

void RedState::setup()
{
    resolution[0] = ofGetWindowWidth();
    resolution[1] = ofGetWindowHeight();
    
    ofBackground(0,0,0);
    shader.load("shaderRed/vs.vert","shaderRed/fs.frag");
    
    // GUI
    gui.setup("panel"); // most of the time you don't need a name but don't forget to call setup
    //    gui.add(filled.set("bFill", true));
    gui.add(number.set( "number", 8.0, 0.0, 30.0 ));
    gui.add(len.set( "len", 2.0, 0.0, 10.0 ));
    gui.add(speed.set( "speed", 5.0, 0.0, 10.0 ));
}

void RedState::update()
{
}

void RedState::draw()
{
    float time = ofGetElapsedTimef();
    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Syphon Stuff
    getSharedData().mClient.draw(50, 50);
    
    ofEnableDepthTest();
    
    shader.begin();
        shader.setUniform1f("time", time);
        shader.setUniform1f("number", number);
        shader.setUniform1f("len", len);
        shader.setUniform1f("speed", speed);
        shader.setUniform1f("freq", freq);
        shader.setUniform2fv("resolution", resolution);
        
        //my_vbo.draw(GL_LINES, 0, n_vert);
    
    ofPushMatrix();
    ofTranslate(200, 100);
    
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(ofGetWidth(), 0);
        glVertex2f(ofGetWidth(), ofGetHeight());
        glVertex2f(0, ofGetHeight());
        glEnd();
    
    ofPopMatrix();
        getSharedData().mainOutputSyphonServer.publishScreen();
    shader.end();
    
    // GUI
    ofDisableDepthTest();
    gui.draw();
}

string RedState::getName()
{
	return "red";
}