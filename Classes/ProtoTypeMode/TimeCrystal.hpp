//
//  TimeCrystal.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/11.
//
//

#ifndef TimeCrystal_hpp
#define TimeCrystal_hpp

#include <cocos2d.h>
#include "Crystal.hpp"

class TimeCrystal : public Crystal
{
public:
    ///初期化
    bool init(cocos2d::SpriteBatchNode* batch) override;
    ///create関数
    static TimeCrystal* create(cocos2d::SpriteBatchNode* batch);
    ///破壊された時の処理
    void DestroyFunc() override;
    ///破壊された時の処理　軽負荷
    void DestroyFuncForExplosion() override;
};

#endif /* TimeCrystal_hpp */
