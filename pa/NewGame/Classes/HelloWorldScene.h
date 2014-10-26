#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//カードの種類
enum CardType{
    Clubs = 0,
    Diamonds,
    Hearts,
    Spades
};

//カード
struct Card{
    int number;
    CardType type;
};

//カードを表示する位置
struct PosIndex{
    int x;
    int y;
};

class HelloWorld : public cocos2d::Layer
{
protected:
    //カード情報
    std::vector<Card> _cards;
    
    //カードを初期化する
    void initCards();
    
    //カードを取得する
    Card getCard();
    
    //カードを作成する
    void createCard(PosIndex posIndex);
    
    //ゲーム開始時にカードを１０枚表示する
    void showInitCards();
    
    //ゲームを初期化する
    void initGame();
    
public:
    //HelloWorldクラスのシーンを作成する
    static cocos2d::Scene* createScene();
    
    //初期化処理を行う
    virtual bool init();
    
    //create関数作成マクロ
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
