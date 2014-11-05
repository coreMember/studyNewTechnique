//
//  Meter.h
//  MyCppGame
//
//  Created by たかふく on 2014/10/13.
//
//

#ifndef __MyCppGame__Meter__
#define __MyCppGame__Meter__

#include <iostream>
#include "cocos2d.h"
#include "Config.h"

class Meter : public cocos2d::Sprite
{
private:
    cocos2d::Sprite* m_meterBg;
    cocos2d::Sprite* m_meter;
    const char* getBarFileName(meterType type);
    virtual bool initWithType(meterType type);
    
protected:
    
public:
    Meter();
    virtual ~Meter();
    static Meter* create(meterType type);
    
    void changeBarScale(float size);
};
#endif /* defined(__MyCppGame__Meter__) */
