//
//  Meter.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#include "Meter.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Meter::Meter()
{
}

Meter::~Meter()
{
}

Meter* Meter::create(meterType type)
{
    Meter* pRet = new Meter();
    if(pRet && pRet->initWithType(type)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool Meter::initWithType(meterType type)
{
    if(!Sprite::initWithFile(getBarFileName(type))) {
        return false;
    }
    
    return true;
}

const char* Meter::getBarFileName(meterType blockType) {
    switch (blockType) {
        case meterTypeBg:
            return "meterBarBg.png";
            break;
        case meterTypeNormal:
            return "meterBar.png";
            break;
        default:
            CCAssert(false, "invalid meterType");
            return "";
            break;
    }
}

// バーサイズ変更
void Meter::changeBarScale(float size) {
    this->setScale(size, 1);
}