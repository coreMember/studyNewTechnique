//
//  BulletSprite.h
//  MyGame
//
//  Created by Seromu on 2014. 10. 30..
//
//

#ifndef __MyGame__BulletSprite__
#define __MyGame__BulletSprite__

#include "cocos2d.h"

class BulletSprite: public cocos2d::Sprite {
    
    enum class BulletType
    {
        Solid, // 直線攻撃
        Angle // 角度調整可能な直線攻撃
    };
    
public:
    float bulletVx, bulletVy; // フレームごとに移動する距離
    void scheShoot();
    void shoot(float f);
};

#endif /* defined(__MyGame__BulletSprite__) */
