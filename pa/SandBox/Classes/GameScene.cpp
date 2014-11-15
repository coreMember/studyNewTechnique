//
//  GameScene.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#include "GameScene.h"
#include "Character.h"
USING_NS_CC;

Scene* GameScene::createScene(){
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    createBackground();
    createCharacter();
    return true;
}

void GameScene::createBackground(){
    Size winSize = Director::getInstance()->getWinSize();
    m_background1 = Sprite::create("Background_skyWars.png");
    m_background1->ignoreAnchorPointForPosition(true);
    m_background1->setPosition(Point(0, 0));
    m_background2 = Sprite::create("Background_skyWars.png");
    m_background2->ignoreAnchorPointForPosition(true);
    m_background2->setPosition(Point(0, winSize.height));
    this->addChild(m_background1);
    this->addChild(m_background2);
    scheduleUpdate();
    //schedule(schedule_selector(GameScene::scrollBackground), 0.1f);
}

void GameScene::update(float frame){
    m_background1->setPositionY(m_background1->getPositionY() - m_scrollValue);
    m_background2->setPositionY(m_background1->getPositionY() + m_background1->getContentSize().height - 4);
    
    if(m_background2->getPositionY() == 0){
        m_background1->setPositionY(0);
    }
    
}

void GameScene::createCharacter(){
    auto winSize = Director::getInstance()->getWinSize();
    m_character = Character::createCharacter();
    m_character->setPositionX(winSize.width / 2);
    m_character->setPositionY(m_characterY);
    this->addChild(m_character);
}