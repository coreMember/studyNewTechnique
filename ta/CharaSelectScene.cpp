//  キャラ選択画面
//  CharaSelectScene.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#include "CharaSelectScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Scene* CharaSelectScene::scene() {
    Scene* scene = Scene::create();
    CharaSelectScene* layer = CharaSelectScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool CharaSelectScene::init() {
    if(!Layer::init()) {
        return false;
    }
    
    // キャラ表示
    showChara();
    
    return true;
}

// キャラ表示
void CharaSelectScene::showChara() {
    // バランス
    auto chara1 = MenuItemImage::create("balanceChara1.png", "",CC_CALLBACK_0(CharaSelectScene::chara1ButtonMouseDown, this));
    chara1->setPosition(Point(WIN_SIZE.width/4, WIN_SIZE.height/2));
    auto chara1Text = Label::createWithSystemFont("バランスタイプ", "HiraKakuProN-W6", 26);
    chara1Text->setPosition(Point(chara1->getPositionX(), 400));
    chara1Text->setColor(Color3B::GREEN);
    chara1Text->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(chara1Text);

    
    // パワー
    auto chara2 = MenuItemImage::create("chara2.png", "",CC_CALLBACK_0(CharaSelectScene::chara2ButtonMouseDown, this));
    chara2->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    auto chara2Text = Label::createWithSystemFont("パワータイプ", "HiraKakuProN-W6", 26);
    chara2Text->setPosition(Point(chara2->getPositionX(), 700));
    chara2Text->setColor(Color3B::RED);
    chara2Text->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(chara2Text);

    // テクニック
    auto chara3 = MenuItemImage::create("chara3.png", "",CC_CALLBACK_0(CharaSelectScene::chara3ButtonMouseDown, this));
    chara3->setPosition(Point(WIN_SIZE.width*3/4, WIN_SIZE.height/2));
    auto chara3Text = Label::createWithSystemFont("テクニックタイプ", "HiraKakuProN-W6", 26);
    chara3Text->setPosition(Point(chara3->getPositionX(), 400));
    chara3Text->setColor(Color3B::ORANGE);
    chara3Text->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(chara3Text);
    
    auto menu = Menu::create(chara1, chara2, chara3, NULL);
    menu->setPosition(Point::ZERO);
    
    addChild(menu);
}

// バランスキャラタップ時の処理
void CharaSelectScene::chara1ButtonMouseDown()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::scene(CHARA_TYPE_BALANCE), Color3B::BLACK));
}

// パワーキャラタップ時の処理
void CharaSelectScene::chara2ButtonMouseDown()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::scene(CHARA_TYPE_POWER), Color3B::BLACK));
}

// テクニックキャラタップ時の処理
void CharaSelectScene::chara3ButtonMouseDown()
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, BattleScene::scene(CHARA_TYPE_TECHNIQUE), Color3B::BLACK));
}

// デストラクタ
CharaSelectScene::~CharaSelectScene() {
    log("dest");
}
