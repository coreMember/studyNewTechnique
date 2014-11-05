//
//  GameScene.cpp
//  ElectronicProject
//
//  Created by たかふく on 2014/09/15.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Scene* GameScene::scene() {
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool GameScene::init() {
    if(!Layer::init()) {
        return false;
    }
    
    m_tapFlg = false;
    m_firstFlg = true;
    m_animationFlg = false;
    
    initForVariables();

    // 背景表示
    showBackground();
    
    // ブロック表示
    showBlocks();
    
    // バー表示
    showBar();
    
    // モンスター
    showMonster();
    
    startTapEvent();
    
    // STARTボタン表示
    showButton();
 
    
    return true;
}

void GameScene::initForVariables() {
    m_selectedIndex = -1;
    srand((unsigned)time(NULL));
}

// 背景表示
void GameScene::showBackground() {
    
    m_background = Sprite::create(PNG_BACKGROUND);
    m_background->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    addChild(m_background);
}

int GameScene::getTag(int posIndexX, int posIndexY)
{
    return kTagBaseBlock + posIndexX*100 + posIndexY;
}

// モンスター表示
void GameScene::showMonster()
{
    m_monster = Sprite::create("monster_1.png");
    m_monster->setPosition(Point(WIN_SIZE.width/2, 700));
    addChild(m_monster);
}

// バー表示
void GameScene::showBar()
{
    m_bar = Sprite::create("bar.png");
//    m_bar->setPosition(Point(WIN_SIZE.width/2, 550));
    m_bar->setPosition(Point(120, 550));
    CCLOG("バーサイズ = %f", m_bar->getContentSize().width);
    m_bar->setAnchorPoint(Vec2(0, 0));
    addChild(m_bar);
}

// STARTボタン表示
void GameScene::showButton()
{
    auto startButton = MenuItemImage::create("start.png", "monster_1.png",CC_CALLBACK_0(GameScene::startButtonMouseDown, this));

    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(Point(500, 600));
    
    addChild(menu);
}

// STARTボタン押下時の処理
void GameScene::startButtonMouseDown()
{
    BlockSprite* pPiece = (BlockSprite*)this->getChildByTag(getTag(m_selectedIndex, 0));
    
    
    // 選択したブロックが下向きであれば着火スタート！
    // 下向きでなければやり直し
    bool startFlg = false;
    int currentEndDirection;
    for(int i = 0; i < pPiece->getDirectionArraySize(); i++) {
        if(pPiece->getDirectionArray()[i][0] == 3) {
            CCLOG("着火スタート！");
            currentEndDirection = pPiece->getDirectionArray()[i][1];
            startFlg = true;
            break;
        }
        else if(pPiece->getDirectionArray()[i][1] == 3) {
            CCLOG("着火スタート！");
            currentEndDirection = pPiece->getDirectionArray()[i][0];
            startFlg = true;
            break;
        }
    }
    
    if(startFlg) {
        auto action = ScaleTo::create(1, 0);
        
        pPiece->runAction(action);
        
        m_bar->setScaleX(0.5);
        auto action2 = ScaleTo::create(0.2, 0.8);
        auto action3 = ScaleTo::create(0.7, 1);
        m_monster->runAction(Sequence::create(action2, action3, NULL));
        
        int currentTagX = m_selectedIndex;
        int currentTagY = 0;
        checkNextBlock(currentEndDirection, currentTagX, currentTagY);
    }
}

int GameScene::getNextStartDirection(int currentEndDirection)
{
    switch (currentEndDirection) {
        case kNorth:
            return kSouth;
            break;
        case kEast:
            return kWest;
            break;
        case kSouth:
            return kNorth;
            break;
        case kWest:
            return kEast;
            break;
            
        default:
            CCAssert(false, "invalid currentEndDirection");
            break;
    }
}

void GameScene::checkNextBlock(int prevEndDirection, int prevTagX, int prevTagY)
{
    CCLOG("prevTagX = %d, prevTagY = %d", prevTagX, prevTagY);
    int nextStartDirection = getNextStartDirection(prevEndDirection);
    int nextTagX;
    int nextTagY;
    switch (nextStartDirection) {
        case kNorth:
            nextTagX = prevTagX;
            nextTagY = prevTagY - 1;
            break;
        case kEast:
            nextTagX = prevTagX - 1;
            nextTagY = prevTagY;
            break;
        case kSouth:
            nextTagX = prevTagX;
            nextTagY = prevTagY + 1;
            break;
        case kWest:
            nextTagX = prevTagX + 1;
            nextTagY = prevTagY;
            break;
            
        default:
            CCAssert(false, "invalid nextStartDirection");
            break;
    }
    CCLOG("nextStartDirection = %d, nextTagX = %d, nextTagY = %d", nextStartDirection, nextTagX, nextTagY);
    
    BlockSprite* pPiece = (BlockSprite*)this->getChildByTag(getTag(nextTagX, nextTagY));

    if(pPiece) {
        int nextEndDirection = -1;
        // ↓はまとめたい
        for(int i = 0; i < pPiece->getDirectionArraySize(); i++) {
            if(pPiece->getDirectionArray()[i][0] == nextStartDirection) {
                nextEndDirection = pPiece->getDirectionArray()[i][1];
                break;
            }
            else if(pPiece->getDirectionArray()[i][1] == nextStartDirection) {
                nextEndDirection = pPiece->getDirectionArray()[i][0];
                break;
            }
        }
        CCLOG("nextEndDirection = %d ", nextEndDirection);
        if(nextEndDirection == -1) {
            // 揃っていないのでここで終了！
            CCLOG("しゅーりょーーーー");
        }
        else {
            auto action = ScaleTo::create(2, 0);
            
            pPiece->runAction(action);
            checkNextBlock(nextEndDirection, nextTagX, nextTagY);
        }
    }
    else {
        CCLOG("ねーよん！！");
    }

}

// ブロックを表示
void GameScene::showBlocks()
{
    // 画面サイズ
    CCLOG("縦%f, 横%f", WIN_SIZE.width, WIN_SIZE.height);
    for(int x = 0; x < MAX_BLOCK_X; x++) {
        for(int y = 0; y < MAX_BLOCK_Y; y++) {
            //ランダムでコマを作成
            kBlock blockType = (kBlock)(rand()%kBlockCount);
            
            // コマを作成
            BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
            if(blockWidht == 0) blockWidht = pBlock->getContentSize().width;
            if(blockHeight == 0) blockHeight = pBlock->getContentSize().height;
            pBlock->setPosition(x*blockWidht+blockWidht/2, y*blockHeight+blockHeight/2);
            addChild(pBlock, kZOrderBlock, getTag(x, y));
        }
    }
}

// タップ時のイベント処理
void GameScene::startTapEvent() {
    m_listner = EventListenerTouchOneByOne::create();
    m_listner->setSwallowTouches(true);
    m_listner->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithFixedPriority(m_listner, 100);
}

bool GameScene::onTouchBegan(Touch* touch, Event* event) {
    Point point = Director::getInstance()->convertToGL(touch->getLocationInView());
    
    ;
    if(!m_animationFlg) {
        int posX = -1;
        int posY = -1;
        for(int x = 0; x < MAX_BLOCK_X; x++) {
            if(point.x >= x*blockWidht && point.x <= (x+1)*blockWidht) {
                posX = x;
                break;
            }
        }
        for(int y = 0; y < MAX_BLOCK_Y; y++) {
            if(point.y >= y*blockHeight && point.y <= (y+1)*blockHeight) {
                posY = y;
                break;
            }
        }
        
        BlockSprite* pPiece = (BlockSprite*)this->getChildByTag(getTag(posX, posY));
        if(!pPiece) {
            CCLOG("ねーよ");
            return false;
        }
        if(m_selectedIndex == -1) {
            m_originColor = pPiece->getColor();
        }
        
        if(posY == 0) {
            pPiece->setColor(Color3B(55, 100, 20));
            if(m_selectedIndex != -1 && posX != m_selectedIndex) {
                BlockSprite* pPrevPiece = (BlockSprite*)this->getChildByTag(getTag(m_selectedIndex, 0));
                pPrevPiece->setColor(m_originColor);
            }
            m_selectedIndex = posX;
        }
        
        pPiece->setNextDirection();
        
        m_animationFlg = true;
        
        // ブロックを回転させる
        auto action = RotateBy::create(0.15, 90);
        
        // コールバック
        auto callBack = CallFunc::create( CC_CALLBACK_0(GameScene::animationCallBack, this));
        pPiece->runAction(Sequence::create(action, callBack, NULL));
        
        
        Rect piecePoint = pPiece->getBoundingBox();
        if(piecePoint.containsPoint(point)) {
            CCLOG("触れたお");
        }
        else {
            CCLOG("はずれ");
        }
    }
    
    return true;
}

void GameScene::animationCallBack()
{
    m_animationFlg = false;
}

// デストラクタ
GameScene::~GameScene() {
    log("dest");
    this->getEventDispatcher()->removeEventListener(m_listner);
    
}