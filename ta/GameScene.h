//
//  GameScene.h
//  ElectronicProject
//
//  Created by たかふく on 2014/09/15.
//
//

#ifndef __ElectronicProject__GameScene__
#define __ElectronicProject__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "BlockSprite.h"
#include "Config.h"

#define PNG_BACKGROUND "battleBg.jpg"
#define WIN_SIZE Director::getInstance()->getWinSize()

#define MAX_BLOCK_X 5
#define MAX_BLOCK_Y 4

class GameScene:public cocos2d::Layer
{
private:
    cocos2d::Sprite* m_bar;
    cocos2d::Sprite* m_monster;
protected:
    enum kTag{
        kTagBackground = 1,
        kTagBaseBlock = 10000,
    };
    
    enum kZOrder {
        kZOrderBackground,
        kZOrderBlock,
    };
    
    cocos2d::Sprite* m_background;
    cocos2d::EventListenerTouchOneByOne* m_listner;
    bool m_tapFlg;
    bool m_animationFlg;
    bool m_firstFlg;
    int blockWidht;
    int blockHeight;
    cocos2d::Color3B m_originColor;
    int m_selectedIndex;
    
    void showBackground();
    void startTapEvent();
    int getTag(int posIndexX, int posIndexY);
    
    int getNextStartDirection(int currentEndDirection);
    void checkNextBlock(int prevEndDirection, int prevTagX, int prevTagY);
    void initForVariables();
    void showButton();
    void showMonster();
    void showBar();
    void startButtonMouseDown();
    void showBlocks();
    void animationCallBack();
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    ~GameScene();
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__ElectronicProject__GameScene__) */
