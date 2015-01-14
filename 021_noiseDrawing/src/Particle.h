#pragma once
#include "ofMain.h"

class Particle {

public:
    //コンストラクタ
    Particle();
    // 初期設定
    void setup(ofVec2f position, ofVec2f velocity);
    void setup(float positionX, float positionY, float velocityX, float velocityY);

    // 更新(位置と力)
    void updateVelocity(int mouseX, int mouseY, float rx, float ry, float mx, float my, float px, float py, float ox, float oy);
    void update(int w, int h);
    
    void draw();
    
    ofVec2f position;
    ofVec2f velocity;
};