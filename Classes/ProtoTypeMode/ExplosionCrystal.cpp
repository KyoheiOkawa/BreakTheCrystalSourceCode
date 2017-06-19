//
//  ExplosionCrystal.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/11.
//
//

#include "Common.h"

USING_NS_CC;

bool ExplosionCrystal::init(SpriteBatchNode* batch)
{
    //このブロックではCrystalクラスをbaseクラスと呼ぶ
    typedef Crystal base;
    
    //親クラスのinit関数をここで呼び出す
    base::init(batch);
    
    //色変更　赤
    this->setColor(Color3B(244, 66, 66));
    
    return true;
}

ExplosionCrystal* ExplosionCrystal::create(SpriteBatchNode* batch)
{
    ExplosionCrystal *pRet = new(std::nothrow) ExplosionCrystal();
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
void ExplosionCrystal::DestroyFunc()
{
    criadx2le::playCueById(SE_EXPLOSION);
    setParticle("particle/Explosion.plist");
    
    MainScene* parent = dynamic_cast<MainScene*>(this->getParent()->getParent()->getParent());
    parent->AddBrokenCrystalCount();
    
    isExplode = true;
    
    //ステージに追加してあるクリスタルにアクセスするため
    auto stage = this->getParent();
    auto crystals = stage->getChildren();
    
    //爆発クリスタルが破壊対象にあった場合に一旦そいつのポインタを保管しておく
    Vector<ExplosionCrystal*> exCrystals;
    
    for(auto crystal : crystals)
    {
        //自分自身だった場合判定を飛ばす
        if(crystal == this)
            continue;
        
        float dis = this->getPosition().getDistance(crystal->getPosition());
        //crystalが爆発の範囲内であったら
        if(dis <= EXPLOSION_RADIUS + ((EXPLOSION_ABILITY * UserDefault::getInstance()->getIntegerForKey("ability3",1))/10.0f))
        {
            //爆発クリスタルの場合、起爆装置が起動していなかったら保管
            //起爆装置が起動していたら無視
            if(dynamic_cast<ExplosionCrystal*>(crystal)){
                auto comp = dynamic_cast<ExplosionCrystal*>(crystal);
                
                if(!comp->GetIsExplode()){
                    exCrystals.pushBack(comp);
                }
            }
            //爆発クリスタル以外は普通に破壊
            else if(dynamic_cast<Crystal*>(crystal)){
                auto comp = dynamic_cast<Crystal*>(crystal);
                comp->DestroyFuncForExplosion();
            }
        }
    }
    //爆発対象になっていた爆発クリスタル達のDestroyFuncを順に実行
    //これは爆発クリスタルの処理を順番に行わないと不正アクセスがどこかで行われてしまうため
    for(auto exc : exCrystals){
        exc->DestroyFunc();
    }
    
    
    this->removeFromParentAndCleanup(true);
}

void ExplosionCrystal::DestroyFuncForExplosion()
{
    DestroyFunc();
}
