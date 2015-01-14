#include "Particle.h"

Particle::Particle(){
    wall = 5;
}

void Particle::setup(ofVec2f _position, ofVec2f _velocity){
    center = _position;
    position = _position;
    velocity = _velocity;
}
void Particle::setup(float positionX, float positionY, float velocityX, float velocityY){
    center = ofVec2f(positionX, positionY);
    velocity = ofVec2f(velocityX, velocityY);
}

// 力をリセット
void Particle::resetForce(){
    force.set(0, 0);
}

// 力を加える
void Particle::addForce(ofVec2f _force){
//    force += _force / mass;
}
void Particle::addForce(float forceX, float forceY){
    force += ofVec2f(forceX, forceY);
}

// 摩擦力の更新
void Particle::updateForce(){
//    force -= velocity * friction;
}

// 位置の更新
void Particle::updatePos(){
    velocity += force;
    position += velocity;
}

// 力の更新と座標の更新をupdateとしてまとめる
void Particle::update(){
    resetForce();
    bounceOffWalls();
    updateForce();
    updatePos();
}

// 描画
void Particle::draw(){
    ofCircle(position, radius);
}

// 画面の端でバウンドする(改定版)
void Particle::bounceOffWalls(){
    float minx = -1 * wall;
    float miny = minx;
    float maxx = -1 * minx;
    float maxy = -1 * miny;
    ofVec2f len = position - center;
    
    if (len.x > maxx){
        len.x = maxx;
        velocity.x *= -1;
    } else if (len.x < minx){
        len.x = minx;
        velocity.x *= -1;
    }
    
    if (len.y > maxy){
        len.y = maxy;
        velocity.y *= -1;
    } else if (len.y < miny){
        len.y = miny;
        velocity.y *= -1;
    }
}
