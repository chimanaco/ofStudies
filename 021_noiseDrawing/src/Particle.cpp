#include "Particle.h"

Particle::Particle(){
}

void Particle::setup(ofVec2f _position, ofVec2f _velocity){
    position = _position;
    velocity = _velocity;
}
void Particle::setup(float positionX, float positionY, float velocityX, float velocityY){
    velocity = ofVec2f(velocityX, velocityY);
}

// 力の更新と座標の更新をupdateとしてまとめる
void Particle::updateVelocity(int _mouseX, int _mouseY, float _rx, float _ry, float _mx, float _my, float _px, float _py, float _ox, float _oy) {
    velocity.x = _rx * (ofNoise(position.y / _px) -_ox);
    velocity.y = _ry * (ofNoise(position.x / _py) -_oy);
}

// 力の更新と座標の更新をupdateとしてまとめる
void Particle::update(int _w, int _h){
    position += velocity;
    
    if(position.x<0)position.x+= _w;
    if(position.x>_w)position.x-= _w;
    if(position.y<0)position.y+= _h;
    if(position.y>_h)position.y-=_h;
}

// 描画
void Particle::draw(){
    ofLine(position.x,position.y,position.x-velocity.x,position.y-velocity.y);
//    ofCircle(position.x, position.y, 1);
    ofNoFill();
//    ofRect(position.x, position.y, 10, 10);
//    ofCircle(position.x, position.y, 3);
//    ofTriangle(position.x, position.y, position.x + 10, position.y + 20, position.x - 10, position.y + 20);
}