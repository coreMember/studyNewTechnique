//
//  WeaponSprite.h
//  MyGame
//
//  Created by Seromu on 2014. 10. 21..
//
//

#ifndef __MyGame__WeaponSprite__
#define __MyGame__WeaponSprite__

#include "cocos2d.h"

class WeaponSprite: public cocos2d::Sprite {
    
public:
    
    // 武器の変化による攻撃タイプ
    enum class AttackType
    {
        Spear,
        Sword
    };
    CC_SYNTHESIZE_READONLY(AttackType, _attackType, attackType); //ボールの種類

};

#endif /* defined(__MyGame__WeaponSprite__) */
