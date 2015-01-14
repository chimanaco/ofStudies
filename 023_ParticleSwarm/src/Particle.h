#pragma once
#include "ofMain.h"

class Particle {

public:
    //コンストラクタ
    Particle();
    // 初期設定
    void setup(ofVec3f position, ofVec3f velocity);
    void setup(float positionX, float positionY, float positionZ, float velocityX, float velocityY, float velocityZ);
    // 力をリセット
    void resetForce();
    // 力を加える
    void addForce(ofVec3f force);
    void addForce(float forceX, float forceY, float forceZ);
    // 力を更新
    void updateForce();
    // 位置の更新
    void updatePos();
    // 更新(位置と力)
    void updateSize(float r);
    // 更新(位置と力)
    void update();
    // 画面からはみ出たらバウンドさせる
    void bounceOffWalls();
    // 画面からはみ出たら反対側から出現
    void throughOfWalls();
    // 描画
    void draw();
    
    // 位置ベクトル
    ofVec3f position;
    // 速度ベクトル
    ofVec3f velocity;
    // 力ベクトル
    ofVec3f force;
    // 摩擦係数
    float friction;
    // パーティクルの半径
    float radius;
    // 固定するかどうか
    bool bFixed;
    // パーティクルの質量
    float mass;
};