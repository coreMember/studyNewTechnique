#ifndef __PuzzleGame__GameLayer__
#define __PuzzleGame__GameLayer__

#include "cocos2d.h"
#include <random>
#include "BallSprite.h"
#include "CoreSprite.h"
#include "CursorSprite.h"
#include "Character.h"

class GameLayer : public cocos2d::Layer
{
protected:
    //ボールチェック方向
    enum class Direction
    {
        x,
        y,
    };
    
    //Zオーダー
    enum ZOrder
    {
        BgForCharacter = 0,
        BgForPuzzle,
        Enemy,
        EnemyHp,
        Char,
        Core,
        CharHp,
        Ball,
        Cursor,
        Level,
        Result
    };
    
    std::default_random_engine _engine; //乱数生成エンジン
    std::discrete_distribution<int> _distForBall; //乱数の分布
    std::uniform_int_distribution<int> _distForMember; //乱数の範囲
    BallSprite* _movingBall; //動かしているボール
    CoreSprite* _movingCore; //動かしているボール
    CursorSprite* _cursor;
    CoreSprite* getTouchCore(cocos2d::Point touchPos);
    bool _movedBall; //他のボールとの接触有無
    bool _movedCore; //他のボールとの接触有無
    bool _touchable; //タップの可否
    int _maxRemovedNo; //一度に削除される最大連鎖の番号
    int _chainNumber; //連鎖数のカウント
    std::vector<std::map<BallSprite::BallType, int>> _removeNumbers; //消去するボールのカウント
    
    Character* _enemyData; //敵の情報
    cocos2d::Sprite* _enemy; //敵画像
    cocos2d::ProgressTimer* _hpBarForEnemy; //敵のヒットポイントバー
    
    cocos2d::Vector<Character*> _memberDatum; //メンバーの情報
    cocos2d::Vector<cocos2d::Sprite*> _members; //メンバー画像
    cocos2d::Vector<cocos2d::ProgressTimer*> _hpBarForMembers; //メンバーのヒットポイントバー

    int getPosFromTag(int tag);
    int _level; //現在のレベル
    int _nextLevel; //次のレベル
    
    void shootCheck(float f);
    void initBackground(); //背景の初期化
    void initEnemy(); //敵の表示
    void initMembers(); //メンバーの表示
    void initCursor();
    void endAnimation(); //アニメーション終了時処理
    cocos2d::Spawn* vibratingAnimation(int afterHp); //振動アニメーション
    
    void initLevelLayer(); //レベル表示レイヤーの表示
    void removeLevelLayer(float dt); //レベル表示レイヤーの削除
    void winAnimation(); //Winアニメーション
    void loseAnimation(); //Loseアニメーション
    void nextScene(float dt); //次のシーンへ遷移
    void attackFromEnemy();
    
public:
    float vx;
    float vy;
    CoreSprite * core;
    
    GameLayer(); //コンストラクタ
    virtual bool init(int level); //初期化
    static GameLayer* create(int level); //create関数生成
    static cocos2d::Scene* createScene(int level = 1); //シーン生成

    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
};

#endif /* defined(__PuzzleGame__GameLayer__) */
