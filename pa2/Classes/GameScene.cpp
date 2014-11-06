#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    showButton();
    makeBlock();
    schedule(schedule_selector(GameScene::updateBlock), 1.0f);
    
    return true;
}

void GameScene::showButton(){
    auto button = ControlButton::create(Scale9Sprite::create("CloseNormal.png"));
    button->setAdjustBackgroundImage(false);
    button->setPosition(200, 300);
    
    button->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::onTouchLeftMove), Control::EventType::TOUCH_UP_INSIDE);
    
    addChild(button);
}

void GameScene::makeBlock()
{

    Size winSize = Director::getInstance()->getWinSize();
    
    for (int i = 0; i < STAGE_WIDTH; i++) {
        for (int j = 0; j < STAGE_HEIGHT; j++) {
            // add "HelloWorld" splash screen"
            auto sprite = Sprite::create("Icon-58.png");
            
            // position the sprite on the center of the screen
//            sprite->setPosition(Vec2(winSize.width * (0.32 + j * 0.04), winSize.height * (0.1 + i * 0.04)));
            sprite->setPosition(BLOCK_SIZE * i + STAGE_DISTANCE_X, BLOCK_SIZE * j + STAGE_DISTANCE_Y);
            
            // add the sprite as a child to this layer
            sprite->setVisible(false);
            spriteArray[i][j] = sprite;
            this->addChild(spriteArray[i][j], 0);
            
            completeTetromino[i][j] = 0;
        }
    }
    
    movingBlockX = startBlockX;
    movingBlockY = startBlockY;
}
void GameScene::updateBlock( float frame )
{
    if(restartBlockFlag == true){
        restartBlockFlag = false;
        movingBlockX = startBlockX;
        movingBlockY = startBlockY;
    }else{
        moveTetris(0, -1);
    }
    
}

void GameScene::moveTetris(int x, int y){
    for (int i = 0; i < STAGE_WIDTH; i++) {
        for (int j = 0; j < STAGE_HEIGHT; j++) {
            if(completeTetromino[i][j] == 1){
                spriteArray[i][j]->setVisible(true);
            }else{
                spriteArray[i][j]->setVisible(false);
            }
        }
    }
    movingBlockX += x;
    movingBlockY += y;
    
    if(movingBlockY == 0){
        saveTetromino();
    }
    if(completeTetromino[movingBlockX][movingBlockY - 1] == 1){
        saveTetromino();
    }
    
    if(restartBlockFlag == false){
        spriteArray[movingBlockX][movingBlockY]->setVisible(true);
    }
    log("%d", movingBlockY);
}

void GameScene::saveTetromino(){
    restartBlockFlag = true;
    spriteArray[movingBlockX][movingBlockY]->setVisible(true);
    completeTetromino[movingBlockX][movingBlockY] = 1;
}

void GameScene::onTouchLeftMove(Ref* sender, Control::EventType controlEvent){
    moveTetris(-1, 0);
}