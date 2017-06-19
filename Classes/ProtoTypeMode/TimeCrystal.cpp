//
//  TimeCrystal.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/11.
//
//

#include "Common.h"

USING_NS_CC;

bool TimeCrystal::init(SpriteBatchNode* batch)
{
    //このブロックではCrystalクラスをbaseクラスと呼ぶ
    typedef Crystal base;
    
    //親クラスのinit関数をここで呼び出す
    base::init(batch);
    
    //色変更　緑
    this->setColor(Color3B(66, 244, 95));
    
    return true;
}

TimeCrystal* TimeCrystal::create(SpriteBatchNode* batch)
{
    TimeCrystal *pRet = new(std::nothrow) TimeCrystal();
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
void TimeCrystal::DestroyFunc()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto userDef = UserDefault::getInstance();
    auto level = userDef->getIntegerForKey("ability2",1);
    
    criadx2le::playCueById(SE_RECOVERY);
    setParticle("particle/TimeEffect.plist");
    MainScene* parent = dynamic_cast<MainScene*>(this->getParent()->getParent()->getParent());
    parent->AddBrokenCrystalCount();
    parent->AddTime(TIME_CRYSTAL_ADD_TIME+((TIME_CRYSTAL_ABILITY*level)/10.0f));
    
    this->removeFromParentAndCleanup(true);
}

void TimeCrystal::DestroyFuncForExplosion()
{
    DestroyFunc();
}
