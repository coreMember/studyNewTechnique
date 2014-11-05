//
//  MeterBar.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/18.
//
//

#include "MeterBar.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

// 初期化
bool MeterBar::init() {
    if(!Node::init()) {
        return false;
    }
    
    _speed = SPEED_NORMAL;
    createBar();
    
    return true;
}

// バー作成
void MeterBar::createBar() {
    // バー背景
    _meterBarBg = Sprite::create("meterBarBg.png");
    _meterBarBg->setAnchorPoint(Point::ZERO);
    _meterBarWidth = _meterBarBg->getContentSize().width;
    this->addChild(_meterBarBg);
    
    // バー本体
    _meterBar = Sprite::create("meterBar.png");
    _meterBar->setAnchorPoint(Point::ZERO);
    _meterBar->setPosition(Point(11, 10));
    this->addChild(_meterBar);

    _currentDirection = PLUS;
}

void MeterBar::startBarMoving() {
    this->scheduleUpdate();
}

void MeterBar::stopBarMoving() {
    this->unscheduleUpdate();
}

void MeterBar::update(float delta) {
    if(_currentScale == 0) {
        _currentDirection = PLUS;
        _currentScale += _speed;
    }
    else if(_currentScale == 100) {
        _currentDirection = MINUS;
        _currentScale -= _speed;
    }
    else {
        if(_currentDirection == PLUS) {
            _currentScale += _speed;
        }
        else if(_currentDirection == MINUS) {
            _currentScale -= _speed;
        }
    }
    if(_currentScale >= 100) {
        _currentScale = 100;
    }
    else if(_currentScale <= 0) {
        _currentScale = 0;
    }
    float value = _currentScale/100;
    
    _meterBar->setScaleX(value);
}

// デストラクタ
MeterBar::~MeterBar() {
    log("dest");
}