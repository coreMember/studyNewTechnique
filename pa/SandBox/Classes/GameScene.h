//
//  GameScene.h
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#ifndef __SandBox__GameScene__
#define __SandBox__GameScene__

#include <stdio.h>
#include <cocos2d.h>
#include <MenuLayer.h>
#include <Character.h>

#define SCROLL_BACKGROUND_VALUE 4;

class GameScene:public cocos2d::Layer{
protected:
    const int m_scrollValue = 4;
    const int m_characterY = 100;
    cocos2d::Sprite* m_background1;
    cocos2d::Sprite* m_background2;
    Character* m_character;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    void createBackground();
    void createCharacter();
    virtual void update(float frame);
};

#endif /* defined(__SandBox__GameScene__) */
