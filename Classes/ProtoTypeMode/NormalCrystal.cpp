//
//  NormalCrystal.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//

#include "Common.h"

USING_NS_CC;

bool NormalCrystal::init(SpriteBatchNode* batch)
{
    //このブロックではCrystalクラスをbaseクラスと呼ぶ
    typedef Crystal base;
    
    //親クラスのinit関数をここで呼び出す
    base::init(batch);
    
    //色変更　水色
    this->setColor(Color3B(132,240,250));
    
    return true;
}

NormalCrystal* NormalCrystal::create(SpriteBatchNode* batch)
{
    {
        NormalCrystal *pRet = new(std::nothrow) NormalCrystal();
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
    
}

//クリスタルが壊れる時の処理をここに記述
void NormalCrystal::DestroyFunc()
{
    MainScene* parent = dynamic_cast<MainScene*>(this->getParent()->getParent()->getParent());
    
    setParticle("particle/Break2.plist");
    
    parent->AddBrokenCrystalCount();
    if(random(0, 1) == 1)
        criadx2le::playCueById(SE_GLASS_BREAK);
    this->removeFromParentAndCleanup(true);
}

void NormalCrystal::DestroyFuncForExplosion()
{
    MainScene* parent = dynamic_cast<MainScene*>(this->getParent()->getParent()->getParent());
    
    parent->AddBrokenCrystalCount();
    this->removeFromParentAndCleanup(true);
}
