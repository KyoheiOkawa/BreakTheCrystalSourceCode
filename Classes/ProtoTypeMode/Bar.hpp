//
//  Bar.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef Bar_hpp
#define Bar_hpp

#include <cocos2d.h>

/**
 *@class Bar
 *@brief バークラス
 */
class Bar : public cocos2d::Sprite
{
public:
    /**
     *@brief                 初期化関数
     *@param[in] length      バーの長さ
     *@param[in] pos         生成する位置（バーの中心の位置）
     *@param[in] rotation    バーの傾き
     *@return    true        初期化成功
     *@return    false       初期化失敗
     */
    bool init(const float length,const cocos2d::Vec2 pos,const float rotation);
    
    /**
     *@brief                 クリエート関数
     *@param[in] length      バーの長さ
     *@param[in] pos         生成する位置（バーの中心の位置）
     *@param[in] rotation    バーの傾き
     *@return                作成されたバーのインスタンスのポインター
     */
    static Bar* create(const float length,const cocos2d::Vec2 pos,const float rotation);
    
private:
    /**
     *@brief                 衝突を検知した瞬間に呼ばれる関数
     *@param[in] &contact    衝突したオブジェクトの情報
     */
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    
    /**
     *@brief                 PhysicsBodyの初期化関数
     */
    void initPhysicsBody();
    
    /**
     *@brief                 バーがどんどん消えていくアクションを設定
     */
    void barAction();
};

#endif /* Bar_hpp */
