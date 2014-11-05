//
//  Pendulum.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/19.
//
//

#ifndef __MyCppGame__Pendulum__
#define __MyCppGame__Pendulum__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"


#define PENDULUM_SPEED_EASY 0.2
#define PENDULUM_SPEED_NORMAL 0.5
#define PENDULUM_SPEED_HARD 0.8

class Pendulum:public cocos2d::Node
{
private:
    void createPendulum();
    cocos2d::Sprite* _pendulumCenter;
    cocos2d::Sprite* _pendulum;

	float rot;		// 重りの角度
	float rot_spd;	// 角速度
	float length;	// 紐の長さ
	float g;		// 重力加速度

public:
    virtual bool init();
    CREATE_FUNC(Pendulum);
    ~Pendulum();
    
    // 移動開始
    void startPendulumMoving();
    void update(float delta);

    // 中心と振り子間の距離取得
    float getDistance();
    
    // 停止
    void stopPendulumMoving();
};

#endif /* defined(__MyCppGame__Pendulum__) */
