#include "GameLayer.h"

#define BALL_NUM_X 6
#define BALL_NUM_Y 4
#define CORE_NUM 5
#define WINSIZE Director::getInstance()->getWinSize()
#define TAG_LEVEL_LAYER 10000

USING_NS_CC;

//コンストラクタ
GameLayer::GameLayer()
: _movingBall(nullptr)
, _touchable(true)
, _level(0)
, _nextLevel(0)
{
    //乱数初期化および各ボールの出現の重みを指定
    std::random_device device;
    _engine = std::default_random_engine(device());
    _distForBall = std::discrete_distribution<int>{20, 20, 20, 20, 20, 10};
    _distForMember = std::uniform_int_distribution<int>(0, 4);
}

//シーン生成
Scene* GameLayer::createScene(int level)
{
	auto scene = Scene::create();
	auto layer = GameLayer::create(level);
    scene->addChild(layer);

    return scene;
}

//インスタンス生成
GameLayer* GameLayer::create(int level)
{
    GameLayer *pRet = new GameLayer();
    pRet->init(level);
    pRet->autorelease();
    
    return pRet;
}

//初期化
bool GameLayer::init(int level)
{
    if (!Layer::init())
        return false;
    
    // シングルタップイベントの取得
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    _level = level; //レベルの保持
    
    initBackground(); //背景の初期化
    initEnemy(); //敵の表示
    initMembers(); //メンバーの表示
    initCursor();
    initLevelLayer(); //レベル表示レイヤーの表示
    
    this->schedule(schedule_selector(GameLayer::attackFromEnemy), 5.0f);
    this->schedule(schedule_selector(GameLayer::shootCheck), 0.1f);

    return true;
}

//背景の初期化
void GameLayer::initBackground()
{
    // キャラクター部の背景
    auto bgForCharacter = Sprite::create("Background1.png");
    bgForCharacter->setAnchorPoint(Point(0, 1));
    bgForCharacter->setPosition(Point(0, WINSIZE.height));
    addChild(bgForCharacter, ZOrder::BgForCharacter);
    
    //パズル部の背景
    auto bgForPuzzle = Sprite::create("Background2.png");
    bgForPuzzle->setAnchorPoint(Point::ZERO);
    bgForPuzzle->setPosition(Point::ZERO);
    addChild(bgForPuzzle, ZOrder::BgForPuzzle);
}

bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
	if(!_touchable){
		return false;
	}
    
	_movingCore = getTouchCore(touch->getLocation());

    if(_movingCore && _movingCore->_timerPhase == CoreSprite::TimerPhase::Ready)
    {
        _cursor->setPosition(Point(getPosFromTag(_movingCore->getTag()), 20));
        _cursor->setVisible(false);
		return true;
    }else
		return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    if(_movingCore->_timerPhase == CoreSprite::Dead)
        return;
    
    _cursor->setVisible(true);
    
    //スワイプとともにボールを移動する
    //_movingCore->setPosition(_movingCore->getPosition() + Point(touch->getDelta().x, 0));
    
    int tag = _movingCore->getTag();
    float angle = (touch->getLocation().x - getPosFromTag(tag - 2)) / (getPosFromTag(tag + 2) - getPosFromTag(tag - 2)) * 180 - 90;
    _cursor->setRotation(angle);
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
    if(_movingCore->_timerPhase == CoreSprite::Dead)
        return;
    
    int tag = _movingCore->getTag();
    float angle = (touch->getLocation().x - getPosFromTag(tag - 2)) / (getPosFromTag(tag + 2) - getPosFromTag(tag - 2)) * 180 - 90;
    float speed = 20;
    
    vx = sin(angle * M_PI / 180) * speed;
    vy = cos(angle * M_PI / 180) * speed;

    auto bullet = (BulletSprite *) Sprite::create("darkstar.png");
    bullet->setPosition(Point(getPosFromTag(_movingCore->getTag()), 40));
    bullet->bulletVx = vx;
    bullet->bulletVy = vy;
    bullet->scheShoot();
    addChild(bullet, ZOrder::Core);
    _bullets.pushBack(bullet);
    
    
    coreAnimation(_movingCore, CoreSprite::TimerPhase::Cooling, 10.0f);
    
    _movingCore->setPositionX(getPosFromTag(_movingCore->getTag()));
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    //onTouchEnded(touch, unused_event);
}

void GameLayer::shootCheck(float f)
{
    for(auto bullet : _bullets)
    {
        // ダメージ判定
        if(bullet->getBoundingBox().intersectsRect(_enemy->getBoundingBox()))
        {
            if(bullet->getBoundingBox().intersectsRect(_enemyData->core->getBoundingBox()))
                attacktoEnemy(1000);
            else
                attacktoEnemy(100);
        }
        
        // out of range
        if(bullet->getPositionX() > WINSIZE.width || bullet->getPositionX() < 0 ||
           bullet->getPositionY() > WINSIZE.height || bullet->getPositionY() < 0)
        {
            _bullets.erase(_bullets.getIndex(bullet));
            this->removeChild(bullet);
        }
    }
}

void GameLayer::attacktoEnemy(int dmg)
{
    // 敵のHPを取得する
    float preHpPercentage = _enemyData->getHpPercentage();
    
    //ダメージをセットする
    int afterHp = _enemyData->getHp() - dmg;
    if (afterHp < 0) afterHp = 0;
    _enemyData->setHp (afterHp);
    
    //敵ヒットポイントバーのアニメーション
    auto act = ProgressFromTo::create(0.5, preHpPercentage, _enemyData->getHpPercentage());
    _hpBarForEnemy->runAction(act);
    
    //敵の被ダメージアニメーション
    _enemy->runAction(vibratingAnimation(afterHp));
    
    if(_enemyData->getHp() <= 0)
    {
        winAnimation();
    }
    
}

CoreSprite* GameLayer::getTouchCore(Point touchPos)
{
	for (int tag = 0; tag < CORE_NUM; tag++)
	{
		auto core = (CoreSprite*)(getChildByTag(tag));
		if (core)
		{
			//2点間の距離を求める
			float distance = core->getPosition().getDistance(touchPos);

			//ボールの当たり判定は円形。つまりボールの中心からの半径で判断する
			if (distance <= CORE_SIZE / 2)
			{
				//タップした位置にボールが存在する
				return core;
			}
		}
	}

	return nullptr;
}

void GameLayer::initEnemy()
{
    //敵の情報
    _enemyData = Character::create();
    _enemyData->retain();
    _enemyData->setMaxHp(10000 * _level);
    _enemyData->setHp(10000 * _level);
    _enemyData->setType(Character::Type::Wind);
    _enemyData->setTurnCount(3);
    _enemyData->coolTime = 3.0f;
    
    //敵の表示
    _enemy = Sprite::create(StringUtils::format("Enemy%d.png", _level));
    _enemy->setPosition(Point(320, 330 + (WINSIZE.height - 660) / 2));
    addChild(_enemy, ZOrder::Enemy);
    
    //敵ヒットポイントバー枠の表示
    auto hpBg = Sprite::create("HpEnemyBackground.png");
    hpBg->setPosition(Point(320, 200 + (WINSIZE.height - 660) / 2));
    addChild(hpBg, ZOrder::EnemyHp);
    
    //敵ヒットポイントバーの表示
    _hpBarForEnemy = ProgressTimer::create(Sprite::create("HpEnemyRed.png"));
    _hpBarForEnemy->setPosition(Point(hpBg->getContentSize().width / 2, hpBg->getContentSize().height / 2));
    _hpBarForEnemy->setType(ProgressTimer::Type::BAR);
    _hpBarForEnemy->setMidpoint(Point::ZERO);
    _hpBarForEnemy->setBarChangeRate(Point(1, 0));
    _hpBarForEnemy->setPercentage(_enemyData->getHpPercentage());
    hpBg->addChild(_hpBarForEnemy);
    
    //コアの表示
    auto core = (CoreSprite*)Sprite::create("CorePurple.png");
    _enemyData->core = core;
    core->setPosition(Point(_enemy->getPositionX() - 150, _enemy->getPositionY()));
    addChild(core, ZOrder::Core);
    
    //コアタイマーの表示
    core->timer = ProgressTimer::create(Sprite::create("CorePurple.png"));
    core->timer->setType(ProgressTimer::Type::RADIAL);
    core->timer->setPosition(Point(_enemy->getPositionX() - 150, _enemy->getPositionY()));
    addChild(core->timer, ZOrder::CoreTimer);
    
    //コアタイマー起動
    coreAnimation(core, CoreSprite::TimerPhase::Cooling, _enemyData->coolTime);
    
    auto action_0 = MoveBy::create(1.0f, Point(300, 0));
    auto action_1 = MoveBy::create(1.0f, Point(-300, 0));
    auto seq1 = Sequence::create(action_0, action_1, NULL);
    core->runAction(RepeatForever::create(seq1));
    
    auto action_2 = MoveBy::create(1.0f, Point(300, 0));
    auto action_3 = MoveBy::create(1.0f, Point(-300, 0));
    auto seq2 = Sequence::create(action_2, action_3, NULL);
    core->timer->runAction(RepeatForever::create(seq2));
}

void GameLayer::initMembers()
{
    std::vector<std::string> fileNames
    {
        "CardBlue.png",
        "CardRed.png",
        "CardGreen.png",
        "CardYellow.png",
        "CardPurple.png"
    };
    
    std::vector<std::string> coreFileNames
    {
        "CoreBlue.png",
        "CoreRed.png",
        "CoreGreen.png",
        "CoreYellow.png",
        "CorePurple.png"
    };

    std::vector<Character::Type> types
    {
        Character::Type::Water,
        Character::Type::Fire,
        Character::Type::Wind,
        Character::Type::Holy,
        Character::Type::Shadow,
    };
    
    for (int i = 0; i < fileNames.size(); i++)
    {
        //メンバー
        auto memberData = Character::create();
        memberData->setMaxHp(200);
        memberData->setHp(200);
        memberData->setType(types[i]);
        _membersData.pushBack(memberData);
        
        //メンバーの表示
        auto member = Sprite::create(fileNames[i].c_str());
        member->setPosition(Point(getPosFromTag(i), 80));
        addChild(member, ZOrder::Char);
        
        //コアの表示
        auto core = (CoreSprite*)Sprite::create(coreFileNames[i].c_str());
        memberData->core = core;
        core->setPosition(Point(getPosFromTag(i), 50));
        core->setTag(i);
        addChild(core, ZOrder::Core);
        
        //コアタイマーの表示
        core->timer = ProgressTimer::create(Sprite::create(coreFileNames[i].c_str()));
        core->timer->setType(ProgressTimer::Type::RADIAL);
        core->timer->setPosition(Point(getPosFromTag(i), 50));
        addChild(core->timer, ZOrder::CoreTimer);
        _cores.pushBack(core);
        
        //コアタイマー起動
        coreAnimation(core, CoreSprite::TimerPhase::Cooling, 10.0f);
        
        //メンバーヒットポイントバー枠の表示
        auto hpBg = Sprite::create("HpCardBackground.png");
        hpBg->setPosition(Point(getPosFromTag(i), 20));
        addChild(hpBg, ZOrder::CharHp);
        
        //メンバーヒットポイントバーの表示
        auto hpBarForMember = ProgressTimer::create(Sprite::create("HpCardGreen.png"));
        hpBarForMember->setPosition(Point(hpBg->getContentSize().width / 2, hpBg->getContentSize().height / 2));
        hpBarForMember->setType(ProgressTimer::Type::BAR);
        hpBarForMember->setMidpoint(Point::ZERO);
        hpBarForMember->setBarChangeRate(Point(1, 0));
        hpBarForMember->setPercentage(memberData->getHpPercentage());
        hpBg->addChild(hpBarForMember);
        
        //配列に格納
        _members.pushBack(member);
        _hpBarForMembers.pushBack(hpBarForMember);
    }
}

void GameLayer::initCursor(){
	_cursor = (CursorSprite*) Sprite::create("cursor.png");
	_cursor->setAnchorPoint(Point(0.5, 0));
	_cursor->setPosition(70, 20);
	addChild(_cursor, ZOrder::Cursor);
}

// アニメーション終了時処理
void GameLayer::endAnimation()
{
    // タップを有効にする
    _touchable = true;
}

// 振動アニメーション
Spawn* GameLayer::vibratingAnimation(int afterHp)
{
    // 振動アニメーション
    auto move = Sequence::create(MoveBy::create(0.025, Point( 5, 5)),
                                 MoveBy::create(0.025, Point(-5, -5)),
                                 MoveBy::create(0.025, Point(-5, -5)),
                                 MoveBy::create(0.025, Point( 5, 5)),
                                 MoveBy::create(0.025, Point( 5, -5)),
                                 MoveBy::create(0.025, Point(-5, 5)),
                                 MoveBy::create(0.025, Point(-5, 5)),
                                 MoveBy::create(0.025, Point( 5, -5)),
                                 nullptr);
    
    // ダメージ時に色を赤くする
    Action* tint;
    if (afterHp > 0)
    {
        // HPが0より大きい場合は、元の色に戻す
        tint = Sequence::create(TintTo::create(0, 255, 0, 0),
                                DelayTime::create(0.2),
                                TintTo::create(0, 255, 255, 255),
                                nullptr);
    }
    else
    {
        // HPが0の場合は、赤いままにする
        tint = TintTo::create(0, 255, 0, 0);
    }
    
    return Spawn::create(move, tint, nullptr);
}

//レベル表示レイヤーの表示
void GameLayer::initLevelLayer()
{
    //レベルレイヤーの生成
    auto levelLayer = LayerColor::create(Color4B(0, 0, 0, 191), WINSIZE.width, WINSIZE.height);
    levelLayer->setPosition(Point::ZERO);
    levelLayer->setTag(TAG_LEVEL_LAYER);
    addChild(levelLayer, ZOrder::Level);
    
    //レベルの表示
    auto levelSprite = Sprite::create("Level.png");
    levelSprite->setPosition(Point(WINSIZE.width * 0.45, WINSIZE.height * 0.5));
    levelLayer->addChild(levelSprite);
    
    //レベル数の表示
    auto levelNumPath = StringUtils::format ("%d.png", _level);
    auto levelNumSprite = Sprite::create(levelNumPath.c_str());
    levelNumSprite->setPosition(Point(WINSIZE.width * 0.85, WINSIZE.height * 0.5));
    levelLayer->addChild(levelNumSprite);
    
    //1.5秒後に消えるようにする
    scheduleOnce(schedule_selector(GameLayer::removeLevelLayer), 1.5);
}

//レベル表示レイヤーの削除
void GameLayer::removeLevelLayer(float dt)
{
    //タップ可能とする
    _touchable = true;
    
    //0.5秒で消えるようにする
    auto levelLayer = getChildByTag(TAG_LEVEL_LAYER);
    levelLayer->runAction(Sequence::create(FadeTo::create(0.5, 0),
                                           RemoveSelf::create(),
                                           nullptr));
}

//敵からの攻撃
void GameLayer::attackFromEnemy(float f)
{
//    if (!_enemyData->isAttackTurn())
//    {
//        //敵の攻撃ターンでない場合は、一連の攻撃の処理を終わらせる
//        endAnimation();
//        return;
//    }
    
    //メンバーを1人選択
    int index;
    Character* memberData;
    
    do {
        //ランダムでメンバーを選択
        index = _distForMember(_engine);
        memberData = _membersData.at(index);
        
        //HPが0のメンバーを選択した場合は、再度選択し直す
    } while (memberData->getHp() <= 0);
    
    auto member = _members.at(index);
    auto hpBarForMember = _hpBarForMembers.at(index);
    
    //メンバーにダメージを与える
    float preHpPercentage = memberData->getHpPercentage();
    int afterHp = memberData->getHp() - 80;
    if (afterHp > memberData->getMaxHp()) afterHp = memberData->getMaxHp();
    memberData->setHp(afterHp);
    
    //メンバーヒットポイントバーのアニメーション
    auto act = ProgressFromTo::create(0.5, preHpPercentage, memberData->getHpPercentage());
    hpBarForMember->runAction(act);
    
    //メンバーの被ダメージアニメーション
    member->runAction(vibratingAnimation(afterHp));
    
    //敵の攻撃アニメーション
    auto seq = Sequence::create(MoveBy::create(0.1, Point(0, -50)),
                                MoveBy::create(0.3, Point(0, 50)), nullptr);
    _enemy->runAction(seq);
    
    //キャラクター死亡チェック
    if(afterHp <= 0)
    {
        auto memberCore = _cores.at(index);
        coreAnimation(memberCore, CoreSprite::TimerPhase::Dead);
    }
    
    //味方の全滅チェック
    bool allHpZero = true;
    
    for (auto character : _membersData)
    {
        if (character->getHp() > 0)
        {
            allHpZero = false;
            break;
        }
    }
    
    // アニメーション終了時処理
    CallFunc* func;
    if (allHpZero)
        func = CallFunc::create(CC_CALLBACK_0(GameLayer::loseAnimation, this));
    else
        func = CallFunc::create(CC_CALLBACK_0(GameLayer::endAnimation, this));
    
    coreAnimation(_enemyData->core, CoreSprite::TimerPhase::Cooling, _enemyData->coolTime);
    
    runAction(Sequence::create(DelayTime::create(0.5), func, nullptr));
}

//コアの点滅をOn、Off、dead
void GameLayer::coreAnimation(CoreSprite* core, int phase, float coolTime)
{
    core->_timerPhase = phase;

    switch (phase) {
        case CoreSprite::TimerPhase::Cooling :
        {
            core->runAction(TintTo::create(0, 100, 100, 100));
            core->timer->setVisible(true);
            
            auto timerAnim = ProgressFromTo::create(coolTime, 0.0f, 100.0f);
            auto callFunc = CallFunc::create([this, core](){
                coreAnimation(core, CoreSprite::TimerPhase::Ready);
            });
            auto seq = Sequence::create(timerAnim, callFunc, NULL);
            core->timer->runAction(seq);
            break;
        }
        case CoreSprite::TimerPhase::Ready :
        {
            core->runAction(TintTo::create(0, 255, 255, 255));
            core->timer->setVisible(false);
            break;
        }
        case CoreSprite::TimerPhase::Dead :
        {
            log("Dead");
            core->timer->setVisible(false);
            core->setVisible(false);
            break;
        }
        default:
            break;
    }
}

//Winアニメーション
void GameLayer::winAnimation()
{
    //白い背景を用意する
    auto whiteLayer = LayerColor::create(Color4B(255, 255, 255, 127), WINSIZE.width, WINSIZE.height);
    whiteLayer->setPosition(Point::ZERO);
    addChild(whiteLayer, ZOrder::Result);
    
    //Win画像を表示する
    auto win = Sprite::create("Win.png");
    win->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
    addChild(win, ZOrder::Result);
    
    // 次のレベルを設定（Level3の次はないので、Level1に戻る）
    if (_level >= 3)
        _nextLevel = 1;
    else
        _nextLevel = _level + 1;
    
    //指定秒数後に次のシーンへ
    scheduleOnce(schedule_selector(GameLayer::nextScene), 3);
}

//Loseアニメーション
void GameLayer::loseAnimation()
{
    //黒い背景を用意する
    auto blackLayer = LayerColor::create(Color4B(0, 0, 0, 127), WINSIZE.width, WINSIZE.height);
    blackLayer->setPosition(Point::ZERO);
    addChild(blackLayer, ZOrder::Result);
    
    //Lose画像を表示する
    auto lose = Sprite::create("Lose.png");
    lose->setPosition(Point(WINSIZE.width / 2, WINSIZE.height / 2));
    addChild(lose, ZOrder::Result);
    
    // 次のレベルを設定
    _nextLevel = 1;
    
    //指定秒数後に次のシーンへ
    scheduleOnce(schedule_selector(GameLayer::nextScene), 3);
}

//次のシーンへ遷移
void GameLayer::nextScene(float dt)
{
    // 次のシーンを生成する
    auto scene = GameLayer::createScene(_nextLevel);
    Director::getInstance()->replaceScene(scene);
}

int GameLayer::getPosFromTag(int tag)
{
    return 70 + tag * 125;
}