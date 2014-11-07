#ifndef __tetris__GameScene__
#define __tetris__GameScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#define STAGE_WIDTH 7
#define STAGE_HEIGHT  12

#define BLOCK_SIZE 58
#define STAGE_DISTANCE_X 50
#define STAGE_DISTANCE_Y 100

class GameScene : public cocos2d::Layer
{
private:
    cocos2d::Sprite* spriteArray[STAGE_WIDTH][STAGE_HEIGHT];
    int movingTetromino[STAGE_WIDTH][STAGE_HEIGHT];
    int completeTetromino[STAGE_WIDTH][STAGE_HEIGHT];
    int startBlockX = 3;
    int startBlockY = 11;
    int movingBlockX;
    int movingBlockY;
    int serryTetrominoX;
    int serryTetrominoY;
    int emptyTetrominoCount = STAGE_WIDTH;
    bool restartBlockFlag;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void showButton();
    void makeBlock();
    void updateBlock(float frame);
    void moveTetris(int x, int y);
    void saveTetromino();
    void checkSerryTetromino();
    void serryTetromino(float frame);
    void reflashField();
    
    //タップ
    void onTouchLeftMove(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTouchRightMove(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    void onTouchDownMove(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};


#endif /* defined(__tetris__GameScene__) */
