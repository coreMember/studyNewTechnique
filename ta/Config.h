//
//  Config.h
//  ElectronicProject
//
//  Created by たかふく on 2014/09/15.
//
//

#ifndef ElectronicProject_Config_h
#define ElectronicProject_Config_h

#define WIN_SIZE Director::getInstance()->getWinSize()
#define BGM_NORMAL "bgm_001.mp3"
#define BGM_BATTLE "bgm_002.mp3"

#define SE_TAP "se_tap.mp3"
#define SE_PUNCH "se_punch.mp3"

enum meterType {
    meterTypeBg,
    meterTypeNormal,
};

enum CharaType {
    CHARA_TYPE_BALANCE,
    CHARA_TYPE_POWER,
    CHARA_TYPE_TECHNIQUE,
};
enum kBlock
{
    kBlockCross,
    kBlockDoubleCurve,
    kBlockCurve,
    kBlockStraight,
    kBlockCount,
};

enum kDirection
{
    kNorth = 1,
    kEast,
    kSouth,
    kWest,
    kDirectionCount,
};

#endif
