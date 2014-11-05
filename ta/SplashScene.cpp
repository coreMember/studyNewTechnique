//
//  SplashScene.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#include "SplashScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


Scene* SplashScene::scene() {
    Scene* scene = Scene::create();
    SplashScene* layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool SplashScene::init() {
    if(!Layer::init()) {
        return false;
    }
    
    // 背景表示
    showBackground();
 
    this->scheduleOnce(schedule_selector(SplashScene::toTitleScene), 1.5f);
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_NORMAL);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_NORMAL, true);
    
    return true;
}


// 背景表示
void SplashScene::showBackground() {
    
    m_background = Sprite::create(PNG_SPLASH_BG);
    m_background->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    addChild(m_background);
}

// タイトル画面へ
void SplashScene::toTitleScene(float dt) {
//    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, TitleScene::scene(), Color3B::BLACK));
    Director::getInstance()->replaceScene(TransitionFade::create(2.0f, DifficultySelectScene::scene(), Color3B::BLACK));
}

// デストラクタ
SplashScene::~SplashScene() {
    log("dest");
}