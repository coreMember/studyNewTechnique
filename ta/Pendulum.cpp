//  振り子
//  Pendulum.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/19.
//
//

#include "Pendulum.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

// 初期化
bool Pendulum::init() {
    if(!Node::init()) {
        return false;
    }
    
    createPendulum();

	rot = 0;		// 重りの角度
	rot_spd = 0;	// 角速度
	length = 50;	// 紐の長さ
	g = PENDULUM_SPEED_HARD;		// 重力加速度
    
    return true;
}

void Pendulum::createPendulum() {
    _pendulumCenter = Sprite::create("pendulumCenter.png");
    _pendulumCenter->setPosition(Point(0, -50));
    this->addChild(_pendulumCenter);

    _pendulum = Sprite::create("pendulum.png");
    _pendulum->setPosition(Point::ZERO);
    this->addChild(_pendulum);
}

void Pendulum::startPendulumMoving() {
    this->scheduleUpdate();
}

void Pendulum::stopPendulumMoving() {
    this->unscheduleUpdate();
}

void Pendulum::update(float delta) {
	// 現在の重りの位置
	float rad = rot * M_PI / 180;
	float px = cos(rad) * length;
	float py = sin(rad) * length;
    
	// 重力移動量を反映した重りの位置
	float vx = px;
	float vy = py;
	float t = -(vy * g)/(vx * vx + vy * vy);
	float gx = px + t * vx;
	float gy = py + g + t * vy;
    
	// ２つの重りの位置の角度差
	float r = atan2(gy,gx) * 180 / M_PI;
    
	// 角度差を角速度に加算
	float sub = r - rot;
	sub -= floor(sub / 360.0) * 360.0;
	if(sub <-180.0)	sub += 360.0;
	if(sub > 180.0)	sub -= 360.0;
	rot_spd += sub;
    
	// 角度に角速度を加算
	rot += rot_spd;
	
	// 新しい重りの位置
	rad = rot * M_PI / 180;
	px = cos(rad) * length;
	py = sin(rad) * length;

	// 重りの座標
    _pendulum->setPosition(Point(px, -py));

    float value = 71 - (int)floor(_pendulumCenter->getPosition().distance(_pendulum->getPosition()));
    float value2 = (value/71)*100;
    if(value2 > 80 && value2 < 101) {
        CCLOG("value = %f", value2);
    }

    // 衝突判定
    BlendFunc blend;
    
    if(_pendulum->getBoundingBox().containsPoint(_pendulumCenter->getPosition())){
        blend.src = GL_SRC_ALPHA;
        blend.dst = GL_ONE;
    }else{
        blend.src = GL_SRC_ALPHA;
        blend.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
    _pendulum->setBlendFunc(blend);
}

float Pendulum::getDistance() {
    return _pendulumCenter->getPosition().distance(_pendulum->getPosition());
}

// デストラクタ
Pendulum::~Pendulum() {
    log("dest");
}