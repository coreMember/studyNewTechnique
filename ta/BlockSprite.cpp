//
//  BlockSprite.cpp
//  ElectronicProject
//
//  Created by たかふく on 2014/09/15.
//
//

#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
}

BlockSprite::~BlockSprite()
{
}

BlockSprite* BlockSprite::createWithBlockType(kBlock blockType)
{
    BlockSprite* pRet = new BlockSprite();
    if(pRet && pRet->initWithBlockType(blockType)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BlockSprite::initWithBlockType(kBlock blockType)
{
    if(!Sprite::initWithFile(getBlockImageFileName(blockType))) {
        return false;
    }
    
    setFirstDirection(blockType);
    
    m_blockType = blockType;
    
    return true;
}

const char* BlockSprite::getBlockImageFileName(kBlock blockType) {
    switch (blockType) {
        case kBlockCross:
            return "1.png";
            break;
        case kBlockDoubleCurve:
            return "2.png";
            break;
        case kBlockCurve:
            return "3.png";
            break;
        case kBlockStraight:
            return "4.png";
            break;
        default:
            CCAssert(false, "invalid blockType");
            return "";
            break;
    }
}

void BlockSprite::setFirstDirection(kBlock blockType)
{
    switch (blockType) {
        case kBlockCross:
            m_directionArraySize = 2;
            m_directionArray = new int*[m_directionArraySize];
            m_directionArray[0] = new int[2];
            m_directionArray[0][0] = 1;
            m_directionArray[0][1] = 3;
            m_directionArray[1] = new int[2];
            m_directionArray[1][0] = 2;
            m_directionArray[1][1] = 4;
            break;
            
        case kBlockDoubleCurve:
            m_directionArraySize = 2;
            m_directionArray = new int*[m_directionArraySize];
            m_directionArray[0] = new int[2];
            m_directionArray[0][0] = 1;
            m_directionArray[0][1] = 4;
            m_directionArray[1] = new int[2];
            m_directionArray[1][0] = 2;
            m_directionArray[1][1] = 3;
            break;
        case kBlockCurve:
            m_directionArraySize = 1;
            m_directionArray = new int*[m_directionArraySize];
            m_directionArray[0] = new int[2];
            m_directionArray[0][0] = 1;
            m_directionArray[0][1] = 2;
            break;
        case kBlockStraight:
            m_directionArraySize = 1;
            m_directionArray = new int*[m_directionArraySize];
            m_directionArray[0] = new int[2];
            m_directionArray[0][0] = 1;
            m_directionArray[0][1] = 3;
            break;
        default:
            CCAssert(false, "invalid blockType");
            break;
    }
}

void BlockSprite::setNextDirection()
{
    for(int i = 0; i < m_directionArraySize; i++) {
        for(int j = 0; j < 2; j++) {
            if(m_directionArray[i][j] == 4) {
                m_directionArray[i][j] = 1;
            }
            else {
                m_directionArray[i][j] = m_directionArray[i][j]+1;
            }
        }
    }
}
