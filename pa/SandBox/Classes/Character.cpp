//
//  Character.cpp
//  SandBox
//
//  Created by Park Station on 2014. 11. 15..
//
//

#include "Character.h"
USING_NS_CC;

//Character::Character(){
//    log("Character");
//}
Character::~Character(){
    log("~Character");
}

Character* Character::createCharacter() {
    Character *pChar = new Character();
    if(pChar && pChar->init()) {
        log("true");
        pChar->autorelease();
        return pChar;
    }
    else {
        log("false");
        CC_SAFE_DELETE(pChar);
        return NULL;
    }
}

bool Character::init(){
    loadCharacterImage();
    
    return true;
}

void Character::loadCharacterImage(){
    //Size winSize = Director::getInstance()->getWinSize();
    m_character = Sprite::create("CharacterImage1.png");
    //m_character->setPositionY(m_characterY);
    //m_character->setPositionX(winSize.width / 2);
    this->addChild(m_character);
}