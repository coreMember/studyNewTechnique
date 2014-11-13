#include "Character.h"

USING_NS_CC;

//コンストラクタ
Character::Character()
: _hp(0)
, _maxHp(0)
, _attack(0)
, _type(Type::None)
, _turnCount(0)
, _remainingTurn(0)
{
}

//インスタンス生成
Character* Character::create()
{
    Character *pRet = new Character();
    pRet->autorelease();
    
    return pRet;
}

//攻撃ターン数取得
int Character::getTurnCount()
{
    return _turnCount;
}

//攻撃ターン数設定
void Character::setTurnCount(int turnCount)
{
    _turnCount = turnCount;
    _remainingTurn = _turnCount;
}

//ヒットポイント（％値）取得
float Character::getHpPercentage()
{
    return _hp * 100.f / _maxHp;
}