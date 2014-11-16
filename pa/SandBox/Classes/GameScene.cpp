//
//  GameScene.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#include "GameScene.h"
#include "Character.h"
#include "Bullet.h"
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
    
    //イベントリスナーを作成
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    
    //イベントリスナーを登録
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
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
    
    m_bullet = Bullet::createBullet();
    this->addChild(m_bullet);
    schedule(schedule_selector(GameScene::updateBullet), 0.05f);
}

void GameScene::updateBullet(float frame){
    if(m_bullet->lastLoadBullet == m_bullet->m_bulletLength){
        m_bullet->lastLoadBullet = 0;
    }
    auto winSize = Director::getInstance()->getWinSize();
    //log("%d", lastLoadBullet);
    auto bullet = m_bullet->m_bulletArray.at(m_bullet->lastLoadBullet);
    bullet->setVisible(true);
    bullet->setPosition(Vec2(m_character->getPositionX() + m_character->getContentSize().width / 2,
                             m_character->getPositionY() + m_character->getContentSize().height + 30));
    auto moveAction = MoveTo::create(1, Vec2(m_character->getPositionX() + m_character->getScaleY() / 2,
                                             winSize.height + 50));
    bullet->runAction(moveAction);
    m_bullet->lastLoadBullet++;
    
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *event){
    log("TouchBegan");
    m_previousPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event){
    log("Touch Moved!");
    auto winSize = Director::getInstance()->getWinSize();
    Point touchPoint = Vec2(touch->getLocationInView().x, touch->getLocationInView().y);
    
    m_character->setPositionX(m_character->getPositionX() - (m_previousPoint.x - touchPoint.x) * 1);
    log("%f", m_character->getPositionX());
    if(m_character->getPositionX() < 0){
        m_character->setPositionX(0);
    }else if(m_character->getPositionX() > winSize.width){
        m_character->setPositionX(winSize.width);
    }
    m_previousPoint = touchPoint;
}

void GameScene::onTouchEnded(Touch *touch, Event *event){
    log("Touch Ended!");
}

void GameScene::onTouchCancelled(Touch *touch, Event *event){
    log("Touch Ended!");
    
}