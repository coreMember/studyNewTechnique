#ifndef __tetris__GameScene__
#define __tetris__GameScene__

#include "cocos2d.h"

#define STAGE_WIDTH 7
#define STAGE_HEIGHT  12

#define BLOCK_SIZE 58
#define STAGE_DISTANCE_X 50
#define STAGE_DISTANCE_Y 100

class GameScene : public cocos2d::Layer
{
private:
    cocos2d::Sprite* spriteArray[STAGE_WIDTH][STAGE_HEIGHT];
    int blockX = 3;
    int blockY = 12;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void makeBlock();
    void updateBlock(float frame);
    void setTimer();
    void newBlock();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};


#endif /* defined(__tetris__GameScene__) */
