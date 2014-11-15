//
//  MenuLayer.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#include "MenuLayer.h"
#include "GameScene.h"
USING_NS_CC;

//初回シーンを生成するメソッド
Scene* MenuLayer::createScene(){
    auto scene = Scene::create();
    auto layer = MenuLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MenuLayer::init(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto titleLabel = LabelTTF::create("SkyWars 1", "Arial", 40);
    titleLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                                 origin.y + visibleSize.height/2 + 300));
    this->addChild(titleLabel);
    
    auto startText = Label::createWithSystemFont("Start", "Arial", 35);

    auto startButton = MenuItemLabel::create(startText, CC_CALLBACK_1(MenuLayer::gameStart, this));
    
    Menu* menu = Menu::create(startButton, NULL);
    
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 200));
    this->addChild(menu);
    
    return true;
}

void MenuLayer::gameStart(Ref* pSender){
    log("Game Start!");

    Scene *pScene = GameScene::createScene();
    Director:: getInstance()->replaceScene(pScene);

    
}

