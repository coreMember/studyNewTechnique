//
//  FigureEightPoint.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/18.
//
//

#ifndef __MyCppGame__FigureEightPoint__
#define __MyCppGame__FigureEightPoint__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"


#define POINT_SPEED_EASY 2
#define POINT_SPEED_NORMAL 6
#define POINT_SPEED_HARD 15

class FigureEightPoint:public cocos2d::Node
{
private:
    void createFigureEightPoint();
    cocos2d::Sprite* _point1;
    cocos2d::Sprite* _point2;
    bool _currentDirection;
    
    // スピード
    int _speed;
    // 度数
    float _degree1;
    float _degree2;
    
    // 半径
    float _radius;
    
public:
    virtual bool init();
    CREATE_FUNC(FigureEightPoint);
    ~FigureEightPoint();
    
    // 移動開始
    void startPointMoving();
    void update(float delta);
    
    // ２点間の距離取得
    float getDistance();
    
    // 停止
    void stopPointMoving();
};

#endif /* defined(__MyCppGame__FigureEightPoint__) */
