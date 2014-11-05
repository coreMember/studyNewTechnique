//
//  MeterBar.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/18.
//
//

#ifndef __MyCppGame__MeterBar__
#define __MyCppGame__MeterBar__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

#define PLUS true
#define MINUS false

#define SPEED_EASY 2
#define SPEED_NORMAL 4
#define SPEED_HARD 10

class MeterBar:public cocos2d::Node
{
private:
    void createBar();
    int _speed;
    cocos2d::Sprite* _meterBarBg;
    cocos2d::Sprite* _meterBar;
    bool _currentDirection;
public:
    virtual bool init();
    CREATE_FUNC(MeterBar);
    ~MeterBar();
    
    // setter
    CC_SYNTHESIZE_READONLY(float, _currentScale, CurrentScale);
    CC_SYNTHESIZE_READONLY(float, _meterBarWidth, MeterBarWidth);
    
    // 移動開始
    void startBarMoving();
    void update(float delta);
    
    // 停止
    void stopBarMoving();
};


#endif /* defined(__MyCppGame__MeterBar__) */
