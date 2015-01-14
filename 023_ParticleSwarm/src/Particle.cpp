#include "Particle.h"

Particle::Particle(){
//    radius = 100;
    friction = 0.01;
    mass = 1.0;
    bFixed = false;
}

void Particle::setup(ofVec3f _position, ofVec3f _velocity){
    // 位置を設定
    position = _position;
    // 初期速度を設定
    velocity = _velocity;
}
void Particle::setup(float positionX, float positionY, float positionZ, float velocityX, float velocityY, float velocityZ){
    // 位置を設定
    position = ofVec3f(positionX, positionY, positionZ);
    // 初期速度を設定
    velocity = ofVec3f(velocityX, velocityY, velocityZ);
}

// 力をリセット
void Particle::resetForce(){
    force.set(0, 0, 0);
}

// 力を加える
void Particle::addForce(ofVec3f _force){
    force += _force / mass;
}
void Particle::addForce(float forceX, float forceY, float forceZ){
    force += ofVec3f(forceX, forceY, forceZ);
}

// 摩擦力の更新
void Particle::updateForce(){
    force -= velocity * friction;
}

// 位置の更新
void Particle::updatePos(){
    if (!bFixed) {
        velocity += force;
        position += velocity;
    }
}

// 位置の更新
void Particle::updateSize(float r){
    radius -= 0.02;
}

// 力の更新と座標の更新をupdateとしてまとめる
void Particle::update(){
    updateForce();
    updatePos();
}

// 描画
void Particle::draw(){
    if(radius > 0) {
        ofNoFill();
        ofSetColor(0);
        glLineWidth(2);
        ofCircle(position, radius);
        
        ofFill();
        
        ofSetColor(position.z / 777 * 255, 255, position.z / 777 * 255);
//        ofColor color;
//        color.setHsb(position.z / 255, 0.8, 0.9);
//        ofSetColor(color);
        ofCircle(position, radius);
    }
}