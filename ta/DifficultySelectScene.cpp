//  難易度選択画面
//  DifficultySelectScene.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/11/04.
//
//

#include "DifficultySelectScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Scene* DifficultySelectScene::scene() {
    Scene* scene = Scene::create();
    DifficultySelectScene* layer = DifficultySelectScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool DifficultySelectScene::init() {
    if(!Layer::init()) {
        return false;
    }
    
    // 背景表示
    showBackground();
    
    // 各種ボタン表示
    showButton();
    
    return true;
}

// 背景表示
void DifficultySelectScene::showBackground() {
    m_background = Sprite::create(PNG_TITLE_BG);
    m_background->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    addChild(m_background);
}

// 各種ボタン表示
void DifficultySelectScene::showButton()
{
    // EASY
    auto easyButton = MenuItemImage::create("buttonStory.png", "",CC_CALLBACK_0(DifficultySelectScene::easyButtonMouseDown, this));
    easyButton->setPosition(Point(WIN_SIZE.width/2, 500));
    auto easyText = Label::createWithSystemFont("EASY", "HiraKakuProN-W6", 29);
    easyText->setPosition(Point(WIN_SIZE.width/2, 505));
    
    // NORMAL
    auto normalButton = MenuItemImage::create("buttonBattle.png", "",CC_CALLBACK_0(DifficultySelectScene::normalButtonMouseDown, this));
    normalButton->setPosition(Point(WIN_SIZE.width/2, 400));
    auto normalText = Label::createWithSystemFont("NORMAL", "HiraKakuProN-W6", 29);
    normalText->setPosition(Point(WIN_SIZE.width/2, 405));
    
    // HARD
    auto hardButton = MenuItemImage::create("buttonEndless.png", "",CC_CALLBACK_0(DifficultySelectScene::hardButtonMouseDown, this));
    hardButton->setPosition(Point(WIN_SIZE.width/2, 300));
    auto hardText = Label::createWithSystemFont("HARD", "HiraKakuProN-W6", 29);
    hardText->setPosition(Point(WIN_SIZE.width/2, 305));
    
    auto menu = Menu::create(easyButton, normalButton, hardButton, NULL);
    menu->setPosition(Point::ZERO);
    
    addChild(menu);
    
    addChild(easyText);
    addChild(normalText);
    addChild(hardText);
}

// EASYボタン押下時の処理
void DifficultySelectScene::easyButtonMouseDown()
{
    CCLOG("ストーリーボタンが押されました");
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, CharaSelectScene::scene(), Color3B::BLACK));
}

// NORMALボタン押下時の処理
void DifficultySelectScene::normalButtonMouseDown()
{
    CCLOG("バトルボタンが押されました");
}

// HARDボタン押下時の処理
void DifficultySelectScene::hardButtonMouseDown()
{
    CCLOG("エンドレスボタンが押されました");
}

// デストラクタ
DifficultySelectScene::~DifficultySelectScene() {
    log("dest");
}