//
//  DifficultySelectScene.h
//  MyCppGame
//
//  Created by たかふく on 2014/11/04.
//
//

#ifndef __MyCppGame__DifficultySelectScene__
#define __MyCppGame__DifficultySelectScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"
#include "CharaSelectScene.h"

#endif /* defined(__MyCppGame__DifficultySelectScene__) */

#define PNG_TITLE_BG "titleBg.png"

class DifficultySelectScene:public cocos2d::Layer
{
private:
    // 背景
    cocos2d::Sprite* m_background;
    void showBackground();
    
    // 各種ボタン表示
    void showButton();
    void easyButtonMouseDown();
    void normalButtonMouseDown();
    void hardButtonMouseDown();
    
    void toDifficultySelectScene(float dt);
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(DifficultySelectScene);
    
    ~DifficultySelectScene();
};

