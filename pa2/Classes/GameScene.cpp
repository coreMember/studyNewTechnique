#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* GameScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

/////////////////////////////////////////
//init
/////////////////////////////////////////
bool GameScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    showButton();
    makeBlock();
    schedule(schedule_selector(GameScene::updateBlock), 0.5f);
    
    return true;
}
/////////////////////////////////////////
//ボタンを生成するメソッド
/////////////////////////////////////////
void GameScene::showButton(){
    auto leftButton = ControlButton::create(Scale9Sprite::create("leftArrow.png"));
    leftButton->setAdjustBackgroundImage(false);
    leftButton->setPosition(500, 300);
    leftButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::onTouchLeftMove), Control::EventType::TOUCH_UP_INSIDE);
    addChild(leftButton);
    
    auto rightButton = ControlButton::create(Scale9Sprite::create("rightArrow.png"));
    rightButton->setAdjustBackgroundImage(false);
    rightButton->setPosition(600, 300);
    rightButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::onTouchRightMove), Control::EventType::TOUCH_UP_INSIDE);
    addChild(rightButton);
    
    auto downButton = ControlButton::create(Scale9Sprite::create("downArrow.png"));
    downButton->setAdjustBackgroundImage(false);
    downButton->setPosition(550, 250);
    downButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::onTouchDownMove), Control::
        EventType::TOUCH_UP_INSIDE);
    addChild(downButton);
}
/////////////////////////////////////////
//フィールドを生成するメソッド
/////////////////////////////////////////
void GameScene::makeBlock(){

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
/////////////////////////////////////////
//ループでブロックを更新及び生成するメソッド
/////////////////////////////////////////
void GameScene::updateBlock( float frame ){
    if(restartBlockFlag == true){
        restartBlockFlag = false;
        movingBlockX = startBlockX;
        movingBlockY = startBlockY;
    }else{
        moveTetris(0, -1);
    }
    
}
/////////////////////////////////////////
//ブロックを移動させるメソッド
/////////////////////////////////////////
void GameScene::moveTetris(int x, int y){
    //値を臨時保存
    int temporarilyX = movingBlockX;
    int temporarilyY = movingBlockY;
    //引数の設定
    if(x != 0){
        movingBlockX += x;
    }
    if(y != 0){
        movingBlockY += y;
    }
    
    
    for (int i = 0; i < STAGE_WIDTH; i++) {
        for (int j = 0; j < STAGE_HEIGHT; j++) {
            if(completeTetromino[i][j] == 1){
//                spriteArray[i][j]->setVisible(true);
            }else{
                spriteArray[i][j]->setVisible(false);
            }
        
            //ブロック衝突感知
            if(completeTetromino[movingBlockX][movingBlockY] == 1){
                movingBlockX = temporarilyX;
                movingBlockY = temporarilyY;
                spriteArray[movingBlockX][movingBlockY]->setVisible(true);
                return;
            }
        }
    }
    
    //左右の壁に当たった際
    if(movingBlockX < 0 || movingBlockY < 0 || movingBlockX >= STAGE_WIDTH){
        movingBlockX = temporarilyX;
        movingBlockY = temporarilyY;
        spriteArray[movingBlockX][movingBlockY]->setVisible(true);
        return;
    }
    
    //下の壁に当たった際
    if(movingBlockY == 0){
        saveTetromino();
    }
    //ブロックに当たった際
    if(completeTetromino[movingBlockX][movingBlockY - 1] == 1){
        saveTetromino();
    }
    //引き続きブロック移動させる
    if(restartBlockFlag == false){
        spriteArray[movingBlockX][movingBlockY]->setVisible(true);
    }
}

/////////////////////////////////////////
//ブロックを配置するメソッド
/////////////////////////////////////////
void GameScene::saveTetromino(){
    restartBlockFlag = true;
    spriteArray[movingBlockX][movingBlockY]->setVisible(true);
    completeTetromino[movingBlockX][movingBlockY] = 1;
    checkSerryTetromino();
    }

/////////////////////////////////////////
//一行埋められているかをチェックするメソッド
/////////////////////////////////////////
void GameScene::checkSerryTetromino(){
    bool serryFlag = true;
    for (int i = 0; i < STAGE_HEIGHT; i++) {
        for (int j = 0; j < STAGE_WIDTH; j++) {
            if(completeTetromino[j][i] == 0){
                serryFlag = false;
                break;
            }
            if(j == STAGE_WIDTH - 1 && serryFlag == true){
                serryTetrominoX = j;
                serryTetrominoY = i;
                
                this->unschedule(schedule_selector(GameScene::updateBlock));
                schedule(schedule_selector(GameScene::serryTetromino), 0.1f);
                return;
            }
            
        }
    }

}
/////////////////////////////////////////
//一行埋められた際実行されるメソッド
/////////////////////////////////////////
void GameScene::serryTetromino( float frame ){
    
    emptyTetrominoCount--;
    if(emptyTetrominoCount < 0){
        
        this->unschedule(schedule_selector(GameScene::serryTetromino));
        reflashField();
        emptyTetrominoCount = STAGE_WIDTH;
        return;
    }
    completeTetromino[emptyTetrominoCount][serryTetrominoY] = 0;
    spriteArray[emptyTetrominoCount][serryTetrominoY]->setVisible(false);
    
}
/////////////////////////////////////////
//ブロック座標を更新するメソッド
/////////////////////////////////////////
void GameScene::reflashField(){
    int startCountY = serryTetrominoY;
    for (int i = 0; i < STAGE_WIDTH; i++) {
        for (int j = startCountY; j < STAGE_HEIGHT; j++) {
            if(j == startCountY || j >= STAGE_HEIGHT - 1){
                completeTetromino[i][j] = 0;
            }else if(completeTetromino[i][j] == 1){
                completeTetromino[i][j] = 0;
                completeTetromino[i][j - 1] = 1;
                spriteArray[i][j - 1]->setVisible(true);
            }else{
                spriteArray[i][j]->setVisible(false);
            }
            
        }
    }
    schedule(schedule_selector(GameScene::updateBlock), 0.5f);
}

/////////////////////////////////////////
//左のボタンを押した際のメソッド
/////////////////////////////////////////
void GameScene::onTouchLeftMove(Ref* sender, Control::EventType controlEvent){
    moveTetris(-1, 0);
}

/////////////////////////////////////////
//右のボタンを押した際のメソッド
/////////////////////////////////////////
void GameScene::onTouchRightMove(Ref* sender, Control::EventType controlEvent){
    moveTetris(+1, 0);
}

/////////////////////////////////////////
//下のボタンを押した際のメソッド
/////////////////////////////////////////
void GameScene::onTouchDownMove(Ref* sender, Control::EventType controlEvent){
    moveTetris(0, -1);
}