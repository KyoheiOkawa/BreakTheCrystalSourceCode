//
//  NormalCrystal.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//
//ノーマルクリスタルクラス
#ifndef NormalCrystal_hpp
#define NormalCrystal_hpp

#include <cocos2d.h>
#include "Crystal.hpp"

/**
 *@class NormalCrystal
 *@brief ノーマルクリスタルクラス
 */
//Crystalクラスを継承すれば面倒臭い衝突処理書かなくて良い
//DestroyFuncにボールと当たったときまたは壊れる時の処理を記述する
class NormalCrystal : public Crystal
{
public:
    ///初期化関数
    bool init(cocos2d::SpriteBatchNode* batch) override;
    /**
     *@brief create関数
     *@param batch ノーマルクリスタルの追加先のバッチノード
     *@return 作成されたノーマルクリスタルのポインタ
     */
    static NormalCrystal* create(cocos2d::SpriteBatchNode* batch);
    ///破壊された時の処理
    void DestroyFunc() override;
    ///破壊された時の処理　軽負荷
    void DestroyFuncForExplosion() override;
};

#endif /* NormalCrystal_hpp */
