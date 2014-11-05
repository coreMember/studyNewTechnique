//
//  TitleScene.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#include "TitleScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Scene* TitleScene::scene() {
    Scene* scene = Scene::create();
    TitleScene* layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool TitleScene::init() {
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
void TitleScene::showBackground() {
    
    m_background = Sprite::create(PNG_TITLE_BG);
    m_background->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    addChild(m_background);
}

// 各種ボタン表示
void TitleScene::showButton()
{
    // ストーリーボタン
    auto storyButton = MenuItemImage::create("buttonStory.png", "",CC_CALLBACK_0(TitleScene::storyButtonMouseDown, this));
    storyButton->setPosition(Point(WIN_SIZE.width/2, 500));
    
    // バトルボタン
    auto battleButton = MenuItemImage::create("buttonBattle.png", "",CC_CALLBACK_0(TitleScene::battleButtonMouseDown, this));
    battleButton->setPosition(Point(WIN_SIZE.width/2, 400));
    
    // エンドレスボタン
    auto endlessButton = MenuItemImage::create("buttonEndless.png", "",CC_CALLBACK_0(TitleScene::endlessButtonMouseDown, this));
    endlessButton->setPosition(Point(WIN_SIZE.width/2, 300));
    
    auto menu = Menu::create(storyButton, battleButton, endlessButton, NULL);
    menu->setPosition(Point::ZERO);
    
    addChild(menu);
}

// ストーリーボタン押下時の処理
void TitleScene::storyButtonMouseDown()
{
    CCLOG("ストーリーボタンが押されました");
    
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, CharaSelectScene::scene(), Color3B::BLACK));
}

// バトルボタン押下時の処理
void TitleScene::battleButtonMouseDown()
{
    CCLOG("バトルボタンが押されました");
}

// エンドレスボタン押下時の処理
void TitleScene::endlessButtonMouseDown()
{
    CCLOG("エンドレスボタンが押されました");
}

// デストラクタ
TitleScene::~TitleScene() {
    log("dest");
}