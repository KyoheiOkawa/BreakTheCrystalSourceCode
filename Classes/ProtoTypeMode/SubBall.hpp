//
//  SubBall.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/12.
//
//

#ifndef SubBall_hpp
#define SubBall_hpp

#include <cocos2d.h>
#include "Ball.hpp"

class SubBall : public Ball
{
private:
    ///最初の座標を保管
    cocos2d::Vec2 _firstPos;
    ///一番最初のアップデートかどうか
    bool isFirstUpdate;
protected:
    ///ボールを動かせさせる関数
    void BallMove();
public:
    ///初期化関数
    virtual bool init(const cocos2d::Vec2 pos,cocos2d::SpriteBatchNode* batch);
    /**
     *@brief create関数
     *@param *batch ボールを追加させるSpriteBatchNodeのポインタ
     */
    static SubBall* create(const cocos2d::Vec2 pos,cocos2d::SpriteBatchNode* batch);
    ///アップデート関数
    virtual void update(float delta) override;

};

#endif /* SubBall_hpp */
