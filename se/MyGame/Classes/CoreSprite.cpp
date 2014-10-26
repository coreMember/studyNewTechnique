/*
 * CoreSprite.cpp
 *
 *  Created on: 2014. 9. 27.
 *      Author: Saerom
 */

#include "CoreSprite.h"

void CoreSprite::scheShoot()
{
    schedule(schedule_selector(CoreSprite::shoot));
}

void CoreSprite::shoot(float f)
{
    setPosition(getPositionX() + coreVx, getPositionY() + coreVy);
    setRotation(getRotation() + 5);
}
