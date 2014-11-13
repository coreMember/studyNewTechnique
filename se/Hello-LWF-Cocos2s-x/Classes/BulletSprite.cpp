//
//  BulletSprite.cpp
//  MyGame
//
//  Created by Seromu on 2014. 10. 30..
//
//

#include "BulletSprite.h"

void BulletSprite::scheShoot()
{
    schedule(schedule_selector(BulletSprite::shoot));
}

void BulletSprite::shoot(float f)
{
    setPosition(getPositionX() + bulletVx, getPositionY() + bulletVy);
    setRotation(getRotation() + 5);
}