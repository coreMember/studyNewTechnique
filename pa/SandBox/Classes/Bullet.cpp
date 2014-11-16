//
//  Bullet.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 16..
//
//

#include "Bullet.h"
#include "Character.h"
USING_NS_CC;
USING_NS_CC_EXT;
Bullet::Bullet(){
    log("Bullet");
}
Bullet* Bullet::createBullet(){
    Bullet *pBullet = new Bullet();
    if(pBullet && pBullet->init()) {
        log("true");
        pBullet->autorelease();
        return pBullet;
    }
    else {
        log("false");
        CC_SAFE_DELETE(pBullet);
        return NULL;
    }
}

bool Bullet::init(){
    
    auto winSize = Director::getInstance()->getWinSize();
    
    m_characterSize = Size(Vec2(50, 50));
    //Size bulletSize = bulletSprite->getContentSize();
    //m_bulletLength = winSize.height / bulletSize.height;
    
    for (int i = 0; i < m_bulletLength; i++) {
        auto bulletSprite = cocos2d::Sprite::create("BulletImage1.png");
        //bulletSprite->setPosition(Vec2(m_characterSize.width / 2, m_characterSize.height + 100));
        bulletSprite->setVisible(false);
        this->addChild(bulletSprite);
        m_bulletArray.pushBack(bulletSprite);
    }
    
    
    return true;
}

void Bullet::updateBullet(float frame){
    if(lastLoadBullet == m_bulletLength){
        lastLoadBullet = 0;
    }
    auto winSize = Director::getInstance()->getWinSize();
    //log("%d", lastLoadBullet);
    auto bullet = m_bulletArray.at(lastLoadBullet);
    bullet->setVisible(true);
    bullet->setPosition(Vec2(m_characterSize.width / 2, m_characterSize.height + 10));
    auto moveAction = MoveTo::create(1, Vec2(bullet->getPositionX(), winSize.height + 50));
    bullet->runAction(moveAction);
    lastLoadBullet++;
    
    
}