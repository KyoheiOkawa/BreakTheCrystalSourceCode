//
//  ExplosionCrystal.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/11.
//
//

#ifndef ExplosionCrystal_hpp
#define ExplosionCrystal_hpp

#include <cocos2d.h>
#include "Crystal.hpp"

class ExplosionCrystal : public Crystal
{
private:
    ///起爆していたらtrue
    bool isExplode;
public:
    ///初期化関数
    bool init(cocos2d::SpriteBatchNode* batch) override;
    ///create関数
    static ExplosionCrystal* create(cocos2d::SpriteBatchNode* batch);
    ///壊された時の処理
    void DestroyFunc() override;
    ///壊された時の処理　軽負荷
    void DestroyFuncForExplosion() override;
    /**
     *@brief 起爆されているか(複数の爆発クリスタルがある場合に必要な確認)
     *@return true 起爆されていた場合
     */
    bool GetIsExplode(){
        return isExplode;
    }
};

#endif /* ExplosionCrystal_hpp */
