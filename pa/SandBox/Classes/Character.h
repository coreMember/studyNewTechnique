//
//  Character.h
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#ifndef __SandBox__Character__
#define __SandBox__Character__

#include <stdio.h>
#include <cocos2d.h>

class Character:public cocos2d::Node{
private:
    
    void loadCharacterImage();
    
public:
    virtual bool init();
    static Character* createCharacter();
    cocos2d::Sprite* m_character;
    ~Character();
//    Character();
};

#endif /* defined(__SandBox__Character__) */
