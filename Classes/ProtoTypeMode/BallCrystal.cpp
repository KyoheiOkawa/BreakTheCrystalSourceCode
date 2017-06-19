//
//  BallCrystal.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/12.
//
//

#include "Common.h"

USING_NS_CC;

bool BallCrystal::init(SpriteBatchNode* batch)
{
    //このブロックではCrystalクラスをbaseクラスと呼ぶ
    typedef Crystal base;
    
    //親クラスのinit関数をここで呼び出す
    base::init(batch);
    
    //色変更 紫
    this->setColor(Color3B(223, 66, 244));
    
    return true;
}

BallCrystal* BallCrystal::create(SpriteBatchNode* batch)
{
    BallCrystal *pRet = new(std::nothrow) BallCrystal();
    if (pRet && pRet->init(batch))
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

//クリスタルが壊れる時の処理をここに記述
void BallCrystal::DestroyFunc()
{
    criadx2le::playCueById(SE_BALL_PLUS);
    setParticle("particle/Phantom.plist");

    auto manager = PrototypeModeManager::getInstance();
    
    Vec2 origin;
    Size vs;
    
    manager->MultiResolution(origin, vs);
    
    //大元
    auto parent = this->getParent()->getParent()->getParent();
    auto stage = this->getParent();
    auto mainScene = dynamic_cast<MainScene*>(parent);
    
    auto worldPos = stage->convertToWorldSpace(this->getPosition());
    
    auto subBall = SubBall::create(worldPos,mainScene->_BallBatch);
    parent->addChild(subBall);
    dynamic_cast<MainScene*>(parent)->AddBrokenCrystalCount();
    
    this->removeFromParentAndCleanup(true);
}

void BallCrystal::DestroyFuncForExplosion()
{
    DestroyFunc();
}
