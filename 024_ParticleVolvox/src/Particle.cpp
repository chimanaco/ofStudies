#include "Particle.h"

Particle::Particle(){
//    radius = 100;
    friction = 0.01;
    mass = 1.0;
    bFixed = false;
    c = ofRandom(0.2,0.5);
}

void Particle::setup(ofVec3f _position, ofVec3f _velocity, float _defRadius){
    // set position
    position = _position;
    // set values
    velocity = _velocity;
	defRadius = _defRadius;
	radius = _defRadius;
}
void Particle::setup(float positionX, float positionY, float positionZ, float velocityX, float velocityY, float velocityZ, float _defRadius){
    // set position
    position = ofVec3f(positionX, positionY, positionZ);
    // set values
    velocity = ofVec3f(velocityX, velocityY, velocityZ);
	defRadius = _defRadius;
	radius = _defRadius;
}

// reset force
void Particle::resetForce(){
    force.set(0, 0, 0);
}

// add force
void Particle::addForce(ofVec3f _force){
    force += _force / mass;
}
void Particle::addForce(float forceX, float forceY, float forceZ){
    force += ofVec3f(forceX, forceY, forceZ);
}

// update force
void Particle::updateForce(){
    force -= velocity * friction;
}

// update position
void Particle::updatePos(){
    if (!bFixed) {
        velocity += force;
        position += velocity;
    }
}

// update size
void Particle::updateSize(float r){
    radius -= r;
}

// update color
void Particle::updateColor(float _colorStart, float _colorEnd){
    c1 = _colorStart;
	c2 = _colorEnd;
}

// update
void Particle::update(){
    updateForce();
    updatePos();
    

}

// draw
void Particle::draw(){
    if(radius > 0) {
//		ofRotateX(ofNoise(defRadius * 0.02, 0.01) * 360);
//		ofRotateY(ofNoise(defRadius * 0.01, 0.01) * 360);
//		ofRotateZ(ofNoise(defRadius * 0.03, 0.01) * 360);
        
        ofFill();
        
//        ofSetColor(position.z / 777 * 255, 255, position.z / 777 * 255);
        ofFloatColor color;
        color.setHsb(radius / defRadius * c1 + c2, 0.8, 0.9);
//        color.setHsb(position.z/ 1000 * c1 + c2, 0.8, 0.9);
//        color.setHsb(c, 0.8, 0.9);
        ofSetColor(color);
//        ofSetColor(radius / defRadius * 255, 0, radius / defRadius * 255);
		//ofRect(position, radius, radius);
		//ofDrawSphere(position, radius);
		
        

            ofCircle(position, radius);
    }
}