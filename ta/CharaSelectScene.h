//
//  CharaSelectScene.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#ifndef __MyCppGame__CharaSelectScene__
#define __MyCppGame__CharaSelectScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"
#include "BattleScene.h"

class CharaSelectScene:public cocos2d::Layer
{
private:
    void showChara();
    void chara1ButtonMouseDown();
    void chara2ButtonMouseDown();
    void chara3ButtonMouseDown();
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(CharaSelectScene);
    
    ~CharaSelectScene();
};

#endif /* defined(__MyCppGame__CharaSelectScene__) */
