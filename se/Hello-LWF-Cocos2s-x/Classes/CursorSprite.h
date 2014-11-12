/*
 * CursorSprite.h
 *
 *  Created on: 2014. 9. 27.
 *      Author: Saerom
 */

#ifndef CURSORSPRITE_H_
#define CURSORSPRITE_H_

#include "cocos2d.h"

class CursorSprite: public cocos2d::Sprite {
public:

	enum class CursorType
	{
		Blue, //青
		Red, //赤
		Green, //緑
		Yellow, //黄
		Purple //紫
	};

	CursorSprite();
	virtual ~CursorSprite();
};

#endif /* CURSORPRITE_H_ */
