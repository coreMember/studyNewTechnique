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
    
	enum class Type
	{
		Blue, //青
		Red, //赤
		Green, //緑
		Yellow, //黄
		Purple //紫
	};
    
    enum TimerPhase
    {
        Cooling = 0,
        Ready,
        Dead
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

    CC_SYNTHESIZE(Type, _type, Type);
    //CC_SYNTHESIZE(TimerPhase, _timerPhase, TimerPhase);
    
    
    cocos2d::ProgressTimer * timer;
    int _timerPhase;
    std::string getCoreImageFilePath(Type type);
    
    CoreSprite();
    virtual ~CoreSprite();
};

#endif /* CORESPRITE_H_ */
