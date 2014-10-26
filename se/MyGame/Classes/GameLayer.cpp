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

	if(_movingCore)
    {
        //this->unschedule(schedule_selector(GameLayer::shootCursor));
        _cursor->setPosition(Point(getPosFromTag(_movingCore->getTag()), 20));
        _cursor->setVisible(false);
		return true;
    }else
		return false;
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
    _cursor->setVisible(true);
    
    //スワイプとともにボールを移動する
    _movingCore->setPosition(_movingCore->getPosition() + Point(touch->getDelta().x, 0));
    
    float angle = (_movingCore->getPositionX() - getPosFromTag(0)) / (getPosFromTag(4) - getPosFromTag(0)) * 180 - 90;
    _cursor->setRotation(angle);
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
    float angle = (_movingCore->getPositionX() - getPosFromTag(0)) / (getPosFromTag(4) - getPosFromTag(0)) * 180 - 90;
    float speed = 20;
    
    vx = sin(angle * M_PI / 180) * speed;
    vy = cos(angle * M_PI / 180) * speed;

    core = (CoreSprite *) Sprite::create("darkstar.png");
    core->setPosition(Point(getPosFromTag(_movingCore->getTag()), 40));
    
    log("fff %f %f", vx, vy);
    addChild(core, ZOrder::Core);
    core->coreVx = vx;
    core->coreVy = vy;
    core->scheShoot();
    _movingCore->setPositionX(getPosFromTag(_movingCore->getTag()));
    this->schedule(schedule_selector(GameLayer::shootCheck), 0.1f);
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    //onTouchEnded(touch, unused_event);
}

void GameLayer::shootCheck(float f)
{
    log("ttt %f %f %f", f, vx, vy);
    
    if(core->getBoundingBox().intersectsRect(_enemy->getBoundingBox()))
    {
        int damage = 500;
        // 敵のHPを取得する
        float preHpPercentage = _enemyData->getHpPercentage();
        
        //ダメージをセットする
        int afterHp = _enemyData->getHp() - damage;
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
    _enemyData->setElement(Character::Element::Wind);
    _enemyData->setTurnCount(3);
    
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

    std::vector<Character::Element> elements
    {
        Character::Element::Water,
        Character::Element::Fire,
        Character::Element::Wind,
        Character::Element::Holy,
        Character::Element::Shadow,
    };
    
    for (int i = 0; i < fileNames.size(); i++)
    {
        //メンバー
        auto memberData = Character::create();
        memberData->setMaxHp(200);
        memberData->setHp(200);
        memberData->setElement(elements[i]);
        _memberDatum.pushBack(memberData);
        
        //メンバーの表示
        auto member = Sprite::create(fileNames[i].c_str());
        member->setPosition(Point(getPosFromTag(i), 80));
        addChild(member, ZOrder::Char);
        
        //コアの表示
        auto core = Sprite::create(coreFileNames[i].c_str());
        core->setPosition(Point(getPosFromTag(i), 50));
        core->setTag(i);
        addChild(core, ZOrder::Core);

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