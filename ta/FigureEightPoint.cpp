//  八の字ポイントクラス
//  FigureEightPoint.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/18.
//
//

#include "FigureEightPoint.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

// 初期化
bool FigureEightPoint::init() {
    if(!Node::init()) {
        return false;
    }
    
    createFigureEightPoint();
    _radius = 50;
    _degree2 = 180;
    _speed = POINT_SPEED_NORMAL;
    
    return true;
}

void FigureEightPoint::createFigureEightPoint() {
    _point1 = Sprite::create("point.png");
    this->addChild(_point1);
    
    _point2 = Sprite::create("point.png");
    this->addChild(_point2);
}

void FigureEightPoint::startPointMoving() {
    this->scheduleUpdate();
}

void FigureEightPoint::stopPointMoving() {
    this->unscheduleUpdate();
}

void FigureEightPoint::update(float delta) {
 	// 弧度
    float radian1 = CC_DEGREES_TO_RADIANS(_degree1);
    float radian2 = CC_DEGREES_TO_RADIANS(_degree2);

 	// 位置
    _point1->setPosition(Point(_radius*cos(radian1), _radius*sin(radian1 + radian1)));
    _point2->setPosition(Point(_radius*cos(radian2), _radius*sin(radian2 + radian2)));
 	_degree1 += _speed;
 	_degree2 -= _speed;
    
    // 衝突判定
    BlendFunc blend;
    if(_point1->getBoundingBox().containsPoint(_point2->getPosition())){
        blend.src = GL_SRC_ALPHA;
        blend.dst = GL_ONE;
    }
    else {
        blend.src = GL_SRC_ALPHA;
        blend.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
    _point1->setBlendFunc(blend);
    _point2->setBlendFunc(blend);

    float value = 125 - (int)floor(_point1->getPosition().distance(_point2->getPosition()));
    float value2 = (value/125)*100;
    if(value2 >  80 && value2 < 101) {
        CCLOG("value = %f", value2);
    }
}

float FigureEightPoint::getDistance() {
    return _point1->getPosition().distance(_point2->getPosition());
}


// デストラクタ
FigureEightPoint::~FigureEightPoint() {
    log("dest");
}