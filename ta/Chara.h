//
//  Chara.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/21.
//
//

#ifndef __MyCppGame__Chara__
#define __MyCppGame__Chara__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

#define TYPE_NORMAL 1
#define TYPE_ATTACK 2

class Chara:public cocos2d::Node
{
private:
    CharaType _charaType;
    void createBar();
    int _speed;
    cocos2d::Sprite* _tile;
    cocos2d::Sprite* _tile2;
    cocos2d::Sprite* _charaImageNormal;
    cocos2d::Sprite* _charaImageAttack;
    void createTile();
    void createChara();
    void setComponentPosition();
public:
    virtual bool initWithCharaType(CharaType charaType);
    static Chara* createWithCharaType(CharaType charaType);
    ~Chara();
    
    //キャラモーション変更
    void changeCharaMotion(int type);
    void setTileVisible(bool visible);
};


#endif /* defined(__MyCppGame__Chara__) */
