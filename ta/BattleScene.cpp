//
//  BattleScene.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#include "BattleScene.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Scene* BattleScene::scene(CharaType charaType) {
    Scene* scene = Scene::create();
    BattleScene* layer = BattleScene::createWithCharaType(charaType);
    scene->addChild(layer);
    return scene;
}

BattleScene* BattleScene::createWithCharaType(CharaType charaType) {
    BattleScene *pRet = new BattleScene();
    if(pRet && pRet->initWithCharaType(charaType)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

// 初期化
bool BattleScene::initWithCharaType(CharaType charaType) {
    if(!Layer::init()) {
        return false;
    }
    
    auto userDefault = UserDefault::getInstance();
    CCLOG("値 = %d", userDefault->getIntegerForKey("score"));
    
    
    _charaType = charaType;
    
    // 背景表示
    showBackground();

    // 各種コンポーネントは位置
    setComponent();
    
    // タップ設定
    setTap();
    
    // BGM再生
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BGM_BATTLE);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_BATTLE, true);

    // SE読み込み
    SimpleAudioEngine::getInstance()->preloadEffect(SE_TAP);
    SimpleAudioEngine::getInstance()->preloadEffect(SE_PUNCH);
    SimpleAudioEngine::getInstance()->setEffectsVolume(0.3);
    
    return true;
}

// 背景表示
void BattleScene::showBackground() {
    m_background = Sprite::create(PNG_BATTLE_BG);
    m_background->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/2));
    addChild(m_background);
    
    m_battleFloor = Sprite::create(PNG_BATTLE_FLOOR);
    m_battleFloor->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/4));
    addChild(m_battleFloor);
    
    m_battleFloorDamage = Sprite::create(PNG_BATTLE_FLOOR_DAMAGE);
    m_battleFloorDamage->setPosition(Point(WIN_SIZE.width/2, WIN_SIZE.height/4));
    m_battleFloorDamage->setVisible(false);
    addChild(m_battleFloorDamage);
    
}

// 各種コンポーネント
void BattleScene::setComponent() {
    // 自キャラ
    _selfChara = Chara::createWithCharaType(_charaType);
    _selfChara->setPosition(Point(WIN_SIZE.width/4 - _selfChara->getContentSize().width/2, 300));
    addChild(_selfChara);
    
    // 敵キャラ
    _enemyChara = Chara::createWithCharaType(_charaType);
    _enemyChara->setScaleX(-1);
    _enemyChara->setPosition(Point(WIN_SIZE.width*3/4 - _enemyChara->getContentSize().width/2, 300));
    addChild(_enemyChara);

    // メーター
    _meterBar = MeterBar::create();
    _meterBar->setPosition(Point(WIN_SIZE.width/4+20 - _meterBar->getMeterBarWidth()/2, 160));
    addChild(_meterBar);
    
    _valueMeterBarText = Label::createWithSystemFont("", "HiraKakuProN-W6", 48);
    _valueMeterBarText->setPosition(Point(WIN_SIZE.width/4, 925));
    _valueMeterBarText->setColor(Color3B::RED);
    _valueMeterBarText->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(_valueMeterBarText);
    
    // 八の字ポイント
    _figureEightPoint = FigureEightPoint::create();
    _figureEightPoint->setPosition(Point(WIN_SIZE.width/4, 300));
    _figureEightPoint->setVisible(false);
    addChild(_figureEightPoint);

    _valueFigureEightPointText = Label::createWithSystemFont("", "HiraKakuProN-W6", 48);
    _valueFigureEightPointText->setPosition(Point(WIN_SIZE.width/2, 925));
    _valueFigureEightPointText->setColor(Color3B::BLUE);
    _valueFigureEightPointText->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(_valueFigureEightPointText);
    
    // 振り子
    _pendulum = Pendulum::create();
    _pendulum->setPosition(Point(WIN_SIZE.width/4, 800));
    _pendulum->setVisible(false);
    addChild(_pendulum);
    
    _valuePendulumText = Label::createWithSystemFont("", "HiraKakuProN-W6", 48);
    _valuePendulumText->setPosition(Point(WIN_SIZE.width*3/4, 925));
    _valuePendulumText->setColor(Color3B::GREEN);
    _valuePendulumText->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    addChild(_valuePendulumText);

    // 合計値
    _valueSumText = Label::createWithSystemFont("", "HiraKakuProN-W6", 55);
    _valueSumText->setPosition(Point(WIN_SIZE.width/2, 975));
    _valueSumText->setColor(Color3B::YELLOW);
    _valueSumText->enableShadow(Color4B::BLACK,Size(-2,-4),2);
    _valueSumText->setVisible(false);
    addChild(_valueSumText);
    
    _meterBar->startBarMoving();
}

void BattleScene::setTap() {
    // シングルタッチイベントリスナーを作成する。
    auto listener1 = EventListenerTouchOneByOne::create();
    // スワロータッチモードにするとonTouchBeganメソッドはタッチイベントは他では使われない。
    listener1->setSwallowTouches(true);
    
    // onTouchBeganイベントコールバック関数実装のラムダ式の例
    listener1->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

}

bool BattleScene::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event) {
    if(_currentDisp > EPendulum) {
        return true;
    }
    
    // メーター、八の字ポイント、振り子の順番で表示
    switch (_currentDisp) {
        case EMeterBar:{
            CCLOG("メーター = %f", _meterBar->getCurrentScale());
            _valueMeterBar = (int)floor(_meterBar->getCurrentScale());
            _valueMeterBarText->setString(to_string(_valueMeterBar));
//            _meterBar->stopBarMoving();
//            removeChild(_meterBar);
            _meterBar->setVisible(false);
            
            _figureEightPoint->setVisible(true);
            _figureEightPoint->startPointMoving();
            
            SimpleAudioEngine::getInstance()->playEffect(SE_TAP);
            break;
        }
        case EFigureEightPoint: {
            CCLOG("八の字距離 = %f", _figureEightPoint->getDistance());
            
            float value = 125 - (int)floor(_figureEightPoint->getDistance());
            _valueFigureEightPoint = (int)((value/125)*100);
            _valueFigureEightPointText->setString(to_string(_valueFigureEightPoint));
            _figureEightPoint->stopPointMoving();
            removeChild(_figureEightPoint);
            
            _pendulum->setVisible(true);
            _pendulum->startPendulumMoving();

            SimpleAudioEngine::getInstance()->playEffect(SE_TAP);
            break;
        }
        case EPendulum: {
            CCLOG("振り子距離 = %f", _pendulum->getDistance());
            // 最大値71は仮
            float value = 71 - (int)floor(_pendulum->getDistance());
            CCLOG("value = %f", value);
            _valuePendulum = (int)((value/71)*100);
            _valuePendulumText->setString(to_string(_valuePendulum));
            _pendulum->stopPendulumMoving();
            removeChild(_pendulum);
            
            _selfChara->changeCharaMotion(TYPE_ATTACK);
            
            // 3つの合計値で演出等を決める
            int sum = _valueMeterBar + _valueFigureEightPoint + _valuePendulum;
//            if(sum > 100) {
//                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, CharaSelectScene::scene(), Color3B::BLACK));
//            }
            
            // 各スコアの移動演出
            auto moveAnimation = MoveTo::create(0.5, Point(_valueFigureEightPointText->getPositionX(), _valueFigureEightPointText->getPositionY() +50));
            
            auto callFuncScoreUnite = CallFunc::create(CC_CALLBACK_0(BattleScene::callBackScoreUnite, this));
            auto sequenceScore = Sequence::create(moveAnimation, callFuncScoreUnite, NULL);
            _valueMeterBarText->runAction(sequenceScore);
            _valueFigureEightPointText->runAction(moveAnimation->clone());
            _valuePendulumText->runAction(moveAnimation->clone());
            
            // スコアを保存
            auto userDefault = UserDefault::getInstance();
            userDefault->setIntegerForKey("score", sum);
            userDefault->flush();
            
            // 瓦非表示
            _selfChara->setTileVisible(false);
            
            // 床割れ
            m_battleFloor->setVisible(false);
            m_battleFloorDamage->setVisible(true);
            
            _earthBg = Sprite::create("earth_3.jpg");
            _earthBg->setPosition(WIN_SIZE.width/2, WIN_SIZE.height/2);
            _earthBg->setOpacity(0);
            addChild(_earthBg);
            
            auto actionFadeIn = FadeIn::create(1.5);
            auto actionDelay = DelayTime::create(1);
            auto actionFadeOut = FadeOut::create(1.5);
            
            auto callBackAnimation = CallFunc::create(CC_CALLBACK_0(BattleScene::callBackAnimation, this));
            auto sequence = Sequence::create(actionDelay, actionFadeIn, actionDelay, actionFadeOut, callBackAnimation, NULL);
            _earthBg->runAction(sequence);
            
            SimpleAudioEngine::getInstance()->playEffect(SE_PUNCH);
            break;
        }
        default:
            break;
    }
    _currentDisp++;

    return true;
}

// 数字合体
void BattleScene::callBackScoreUnite() {
    int sum = _valueMeterBar + _valueFigureEightPoint + _valuePendulum;
    _valueMeterBarText->setVisible(false);
    _valueFigureEightPointText->setVisible(false);
    _valuePendulumText->setVisible(false);

    _valueSumText->setVisible(true);
    _valueSumText->setString(StringUtils::toString(sum));
    
    // 拡大
    auto scaleUpAction = ScaleTo::create(0.4, 2);
    _valueSumText->runAction(scaleUpAction);
}

// 一連のアニメーションのコールバック
void BattleScene::callBackAnimation() {
    removeChild(_earthBg);

    _selfChara->changeCharaMotion(TYPE_NORMAL);
    
    // 敵の攻撃
    srand(time(0));
    for(int i = 0; i < 30; i++) {
        CCLOG("乱数 = %d",100+(int)rand()%50);
    }
    _enemyChara->changeCharaMotion(TYPE_ATTACK);
}

// デストラクタ
BattleScene::~BattleScene() {
    log("dest");
}