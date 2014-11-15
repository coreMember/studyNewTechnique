//
//  MenuLayer.h
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#ifndef __SandBox__MenuLayer__
#define __SandBox__MenuLayer__

#include <stdio.h>
#include <cocos2d.h>

class MenuLayer:public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    
    void gameStart(Ref* pSender);
    
};

#endif /* defined(__SandBox__MenuLayer__) */
