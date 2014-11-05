//
//  SplashScene.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#ifndef __MyCppGame__SplashScene__
#define __MyCppGame__SplashScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "DifficultySelectScene.h"

#define PNG_SPLASH_BG "splash.png"

class SplashScene:public cocos2d::Layer
{
private:
    // 背景
    cocos2d::Sprite* m_background;
    void showBackground();

    void showButton();
    void startButtonMouseDown();
    
    void toTitleScene(float dt);

public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(SplashScene);
    
    ~SplashScene();
};

#endif /* defined(__MyCppGame__SplashScene__) */
