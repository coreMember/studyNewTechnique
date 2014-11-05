//
//  TitleScene.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#ifndef __MyCppGame__TitleScene__
#define __MyCppGame__TitleScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

#include "CharaSelectScene.h"

#endif /* defined(__MyCppGame__TitleScene__) */

#define PNG_TITLE_BG "titleBg.png"

class TitleScene:public cocos2d::Layer
{
private:
    // 背景
    cocos2d::Sprite* m_background;
    void showBackground();
    
    // 各種ボタン表示
    void showButton();
    void storyButtonMouseDown();
    void battleButtonMouseDown();
    void endlessButtonMouseDown();
    
    void toTitleScene(float dt);
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(TitleScene);
    
    ~TitleScene();
};

