//
//  SubBall.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/12.
//
//

#include "Common.h"

USING_NS_CC;

bool SubBall::init(const Vec2 pos,SpriteBatchNode* batch)
{
    typedef Ball base;
    
    base::init(batch);
    
    auto userDef = UserDefault::getInstance();
    
    //紫色
    this->setColor(Color3B(220, 0, 255));
    this->setPosition(pos);
    
    this->BallMove();
    
    auto level = userDef->getIntegerForKey("ability1",1);
    auto lifeTime = DelayTime::create(SUB_BALL_LIFETIME+((SUB_BALL_ADD_LIFETIME*level)/10.0f));
    auto death = CallFunc::create([this](){
        this->removeFromParentAndCleanup(true);
    });
    
    
    auto seq = Sequence::create(lifeTime,death , NULL);
    this->runAction(seq);
    
    
    _firstPos = pos;
    isFirstUpdate = true;
    
    return true;
}

SubBall* SubBall::create(Vec2 pos, SpriteBatchNode* batch)
{
    SubBall *pRet = new(std::nothrow) SubBall();
    if (pRet && pRet->init(pos,batch))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

void SubBall::update(float delta)
{
    typedef Ball base;
    
    base::update(delta);
    
    //理由は分からないが、ボールクリスタル破壊された時
    //正しい座標を指定してサブボールを生成するが
    //最初のアップデートで座標が思いもよらぬ座標になってしまう
    //ボールクリスタルでメインボールを試しに生成したみたが
    //同様の現象が起こる
    if(isFirstUpdate){
        isFirstUpdate = false;
        this->setPosition(_firstPos);
    }
}

//ボールが生成された時点でランダムな方向にボールを動かす関数
void SubBall::BallMove()
{
    float rand = random(0, 360);
    Vec2 dir = Vec2(cosf(MATH_DEG_TO_RAD(rand)),sinf(MATH_DEG_TO_RAD(rand)));
    
    dir *= SUB_BALL_FIRSTSPEED;
    this->getPhysicsBody()->applyImpulse(dir);
}
