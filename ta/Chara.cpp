//
//  Chara.cpp
//  MyCppGame
//
//  Created by たかふく on 2014/10/21.
//
//

#include "Chara.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

Chara* Chara::createWithCharaType(CharaType charaType) {
    Chara *pRet = new Chara();
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
bool Chara::initWithCharaType(CharaType charaType) {
    _charaType = charaType;
    createChara();
    createTile();
    setComponentPosition();
    
    return true;
}

// キャラ作成
void Chara::createChara() {
    std::string normalCharaFileName;
    std::string attackCharaFileName;
    switch (_charaType) {
        case CHARA_TYPE_BALANCE:
            normalCharaFileName = "balanceChara1.png";
            attackCharaFileName = "balanceChara2.png";
            break;
        case CHARA_TYPE_POWER:
            normalCharaFileName = "chara2.png";
            attackCharaFileName = "balanceChara2.png";
            break;
        case CHARA_TYPE_TECHNIQUE:
            normalCharaFileName = "chara3.png";
            attackCharaFileName = "balanceChara2.png";
            break;
        default:
            break;
    }
    
    _charaImageNormal = Sprite::create(normalCharaFileName);
    _charaImageNormal->setVisible(true);
    this->addChild(_charaImageNormal);
    
    _charaImageAttack = Sprite::create(attackCharaFileName);
    _charaImageAttack->setVisible(false);
    this->addChild(_charaImageAttack);
}

// 瓦作成
void Chara::createTile() {
    _tile = Sprite::create("tile.png");
    this->addChild(_tile);

    _tile2 = Sprite::create("tile.png");
    this->addChild(_tile2);
}

// 座標設定
void Chara::setComponentPosition() {
    _tile->setPosition(Point(0, 0));
    _tile2->setPosition(Point(0, _tile->getContentSize().height-10));
    _charaImageNormal->setPosition(Point(0, _tile2->getPositionY()+_tile2->getContentSize().height/2+ _charaImageNormal->getContentSize().height/2));
    
    _charaImageAttack->setPosition(Point(0, _tile2->getPositionY()+_tile2->getContentSize().height/2+ _charaImageAttack->getContentSize().height/2));

}

// キャラモーション変更
void Chara::changeCharaMotion(int type) {
    switch (type) {
        case TYPE_NORMAL:
            _charaImageNormal->setVisible(true);
            _charaImageAttack->setVisible(false);
            break;
        case TYPE_ATTACK:
            _charaImageNormal->setVisible(false);
            _charaImageAttack->setVisible(true);
            break;
    };
}

// 瓦表示・非表示
void Chara::setTileVisible(bool visible) {
    _tile->setVisible(visible);
    _tile2->setVisible(visible);
}

// デストラクタ
Chara::~Chara() {
    log("dest");
}