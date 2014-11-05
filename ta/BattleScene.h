//
//  BattleScene.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#ifndef __MyCppGame__BattleScene__
#define __MyCppGame__BattleScene__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"
#include "MeterBar.h"
#include "Chara.h"
#include "FigureEightPoint.h"
#include "Pendulum.h"
#include "CharaSelectScene.h"

#define PNG_BATTLE_BG "battleBg.png"
#define PNG_BATTLE_FLOOR "battleFloor.png"
#define PNG_BATTLE_FLOOR_DAMAGE "battleFloorDamage1.png"

class BattleScene:public cocos2d::Layer
{
private:
    CharaType _charaType;

    // 背景
    cocos2d::Sprite* m_background;
    cocos2d::Sprite* _earthBg;
    
    // 床
    cocos2d::Sprite* m_battleFloor;
    cocos2d::Sprite* m_battleFloorDamage;
    
    void showBackground();

    void setComponent();
    
    // バー
    MeterBar* _meterBar;
    cocos2d::Label* _valueMeterBarText;
    int _valueMeterBar;

    // ポイント
    FigureEightPoint* _figureEightPoint;
    cocos2d::Label* _valueFigureEightPointText;
    int _valueFigureEightPoint;
    
    // 振り子
    Pendulum* _pendulum;
    cocos2d::Label* _valuePendulumText;
    int _valuePendulum;
    
    // 合計値
    cocos2d::Label* _valueSumText;
    
    // 自キャラ
    Chara* _selfChara;
    // 敵キャラ
    Chara* _enemyChara;
    
    void setTap();
    
    // 現在の表示(メーター)
    int _currentDisp = 0;
    
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);

    enum EDisp {
        EMeterBar,
        EFigureEightPoint,
        EPendulum,
    };
    
    void callBackScoreUnite();
    void callBackAnimation();
    
public:
    virtual bool initWithCharaType(CharaType charaType);
    static cocos2d::Scene* scene(CharaType charaType);
    static BattleScene* createWithCharaType(CharaType charaType);
    
    ~BattleScene();
};


#endif /* defined(__MyCppGame__BattleScene__) */
