#pragma once
#include "ofMain.h"

class Particle {

public:
    //コンストラクタ
    Particle();
    // 初期設定
    void setup(ofVec2f position, ofVec2f velocity);
    void setup(float positionX, float positionY, float velocityX, float velocityY);
    // 力をリセット
    void resetForce();
    // 力を加える
    void addForce(ofVec2f force);
    void addForce(float forceX, float forceY);
    // 力を更新
    void updateForce();
    // 位置の更新
    void updatePos();
    // 更新(位置と力)
    void update();
    
    // bounce
    void bounceOffWalls();
    
    void draw();

    ofVec2f center;

    // 位置ベクトルの配列
    ofVec2f position;
    // 速度ベクトルの配列
    ofVec2f velocity;
    // 力ベクトルの配列
    ofVec2f force;
    
    float radius;
    float wall;
};