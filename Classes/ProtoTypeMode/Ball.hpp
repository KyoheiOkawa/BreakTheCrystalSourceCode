//
//  Ball.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef Ball_hpp
#define Ball_hpp

#include <cocos2d.h>
/**
 *@class Ball
 *@brief ボールクラス
 */
class Ball : public cocos2d::Sprite
{
public:
    /**
     *@brief 初期化関数
     *@param _batch ボールを追加するバッチノード
     *@return true 初期化成功
     *@return false 初期化失敗
     */
    virtual bool init(cocos2d::SpriteBatchNode* _batch);
    /**
     *@brief create関数
     *@param _batch ボールを追加するバッチノード
     *@return 作成されたBallクラス
     */
    static Ball* create(cocos2d::SpriteBatchNode* _batch);
    ///衝突を検知した瞬間に呼ばれる
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    ///アップデート関数
    virtual void update(float delta);
    /**
     *@brief ボールを動き出させる関数
     *@param Vec 方向を示す正規化されたベクトル
     */
    virtual void BallMove(const cocos2d::Vec2 Vec);
};

#endif /* Ball_hpp */
