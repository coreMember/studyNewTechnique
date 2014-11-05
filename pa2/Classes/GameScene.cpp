#include "GameScene.h"

USING_NS_CC;

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
    
    makeBlock();
    schedule(schedule_selector(GameScene::updateBlock), 1.0f);
    setTimer();
    newBlock();
    return true;
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
        }
    }
}
void GameScene::updateBlock( float frame )
{
    if(blockY - 1 != STAGE_HEIGHT - 1){
        spriteArray[blockX][blockY]->setVisible(false);
    }
    spriteArray[blockX][blockY - 1]->setVisible(true);
    blockY -= 1;
    log("%d", blockY);
}

void GameScene::setTimer(){
//    schedule(schedule_selector(GameScene::newBlock), 3.0f);
}

void GameScene::newBlock(){
    
}
