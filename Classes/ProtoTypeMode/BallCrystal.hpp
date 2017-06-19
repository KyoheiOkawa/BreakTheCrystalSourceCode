//
//  BallCrystal.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/12.
//
//

#ifndef BallCrystal_hpp
#define BallCrystal_hpp

#include <cocos2d.h>
#include "Crystal.hpp"

class BallCrystal : public Crystal
{
public:
    ///初期化関数
    bool init(cocos2d::SpriteBatchNode* batch) override;
    ///create関数
    static BallCrystal* create(cocos2d::SpriteBatchNode* batch);
    ///破壊された時の処理
    void DestroyFunc() override;
    ///破壊された時の処理　軽負荷
    void DestroyFuncForExplosion() override;
};

#endif /* BallCrystal_hpp */
