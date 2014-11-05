//
//  BlockSprite.h
//  ElectronicProject
//
//  Created by たかふく on 2014/09/15.
//
//

#ifndef __ElectronicProject__BlockSprite__
#define __ElectronicProject__BlockSprite__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::Sprite
{
protected:
    const char* getBlockImageFileName(kBlock blockType);
    void setFirstDirection(kBlock blockType);
    
public:
    CC_SYNTHESIZE_READONLY(kBlock, m_blockType, BlockType);
    CC_SYNTHESIZE_READONLY(int**, m_directionArray, DirectionArray);
    CC_SYNTHESIZE_READONLY(int, m_directionArraySize, DirectionArraySize);
    
    BlockSprite();
    virtual ~BlockSprite();
    virtual bool initWithBlockType(kBlock blockType);
    void setNextDirection();
    static BlockSprite* createWithBlockType(kBlock blockType);
};

#endif /* defined(__ElectronicProject__BlockSprite__) */
