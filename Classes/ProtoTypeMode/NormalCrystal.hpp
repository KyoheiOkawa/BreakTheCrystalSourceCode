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
