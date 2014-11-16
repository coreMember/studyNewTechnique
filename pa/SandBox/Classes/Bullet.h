//
//  Bullet.h
//  SandBox
//
//  Created by Park Station on 2014. 11. 16..
//
//

#ifndef __SandBox__Bullet__
#define __SandBox__Bullet__

#include <stdio.h>
#include <cocos2d.h>
#include "extensions/cocos-ext.h"

class Bullet:public cocos2d::Node{
public:
    static Bullet* createBullet();
    cocos2d::Vector<cocos2d::Sprite*> m_bulletArray;
    cocos2d::Size m_characterSize;
    int m_bulletLength = 20;
    int lastLoadBullet = 0;
    virtual bool init();
    void updateBullet(float frame);
    Bullet();
    
};
#endif /* defined(__SandBox__Bullet__) */
