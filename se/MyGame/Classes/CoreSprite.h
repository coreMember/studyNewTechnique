/*
 * CoreSprite.h
 *
 *  Created on: 2014. 9. 27.
 *      Author: Saerom
 */

#ifndef CORESPRITE_H_
#define CORESPRITE_H_

#include "cocos2d.h"

#define CORE_SIZE 106 //ボールのサイズ

class CoreSprite: public cocos2d::Sprite {
    
public:

	enum class CoreType
	{
		Blue, //青
		Red, //赤
		Green, //緑
		Yellow, //黄
		Purple //紫
	};

	//位置インデックス
	struct PositionIndex
	{
		//コンストラクタ
		PositionIndex()
		{
			x = 0;
		}

		//コンストラクタ
		PositionIndex(int _x)
		{
			x = _x;
		}

		int x; //x方向のインデックス
	};
    
    float coreVx;
    float coreVy;
    void scheShoot();
    void shoot(float f);
};

#endif /* CORESPRITE_H_ */
