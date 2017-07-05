//
//  Crystal.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//

#ifndef Crystal_hpp
#define Crystal_hpp

#include <cocos2d.h>
#include "MainScene.hpp"

/**
 *@class Crystal
 *@brief クリスタルの基底抽象クラス
 */
class Crystal : public cocos2d::Sprite
{
protected:
    ///Mainシーンのポインタ
    MainScene* _parent;
    /**
     *@brief パーティクルを発生させる
     *@param[in] filePath 発生させるパーティクルの.plistのパス
     */
    void setParticle(std::string filePath);
    /**
     *@brief クリスタルが壊れる時のアクションを設定
     */
    void DestroyAction();
public:
    /**
     *@brief 初期化関数
     *@param[in] batch クリスタルを追加するパーティクルバッチノード
     *@return true 初期化成功時
     */
    virtual bool init(cocos2d::SpriteBatchNode* batch);
    ///衝突を検知した時に呼ばれる
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    /**
     @brief クリスタルが破壊される時の処理
     */
    virtual void DestroyFunc() = 0;
    /**
     *@brief 爆発に巻き込まれた時に使用するDestroyFunc
     *
     *処理の負荷を減らすためパーティクルを発生しない、音を鳴らさずにクリスタルを破壊する関数
     *
     */
    virtual void DestroyFuncForExplosion() = 0;
};

#endif /* Crystal_hpp */
