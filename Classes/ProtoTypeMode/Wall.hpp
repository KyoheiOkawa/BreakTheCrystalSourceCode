//
//  Wall.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//
//壁オブジェクトクラス
//画面４方の衝突

#ifndef Wall_hpp
#define Wall_hpp

#include <cocos2d.h>

/**
 *@class Wall
 *@brief 壁オブジェクトクラス
 *見えない壁
 */
class Wall : public cocos2d::Node
{
public:
    ///初期化
    bool init();
    ///create関数マクロ
    CREATE_FUNC(Wall);
};

#endif /* Wall_hpp */
