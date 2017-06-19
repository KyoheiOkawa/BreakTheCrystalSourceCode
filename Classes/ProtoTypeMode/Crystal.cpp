//
//  Crystal.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//

#include "Common.h"


USING_NS_CC;

bool Crystal::init(SpriteBatchNode* batch)
{
    if(!Sprite::initWithTexture(batch->getTexture()))
        return false;
    
    auto pb = PhysicsBody::createCircle(this->getContentSize().width/2);
    pb->setDynamic(false);
    pb->setCategoryBitmask(0x08);
    pb->setContactTestBitmask(0x01);
    pb->setCollisionBitmask(0x00);
    
    this->setPhysicsBody(pb);
    
    this->setTag((int)Tag::CRYSTAL);
    
    this->setScale(1.0f/2.0f);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Crystal::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

bool Crystal::onContactBegin(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto crystal = dynamic_cast<Crystal*>(nodeA);
    if(!crystal){
        crystal = dynamic_cast<Crystal*>(nodeB);
    }
    
    auto ball = dynamic_cast<Ball*>(nodeA);
    if(!ball){
        ball = dynamic_cast<Ball*>(nodeB);
    }
    
    if(!ball || crystal != this){
        return true;
    }
    
    if(crystal){
        DestroyAction();
    }
    
    return true;
}


//破壊された時に発生させるパーティクル
//引数には発生させたいパーティクルのパスを
void Crystal::setParticle(std::string filePath)
{
    auto stage = this->getParent()->getParent();
    auto creater = dynamic_cast<StageCreater*>(stage);
    
    float delta = 0;
    auto target = Application::getInstance()->getTargetPlatform();
    if(target == ApplicationProtocol::Platform::OS_IPAD)
        delta = 64.0f;
    
    Vec2 deltaVec = Vec2(delta,0);
    
    //クリスタルの中でも多くを占めるノーマルクリスタルの破壊された時の
    //パーティクルは、発生させる回数も多いため毎回plistファイルを読み込んでいると
    //処理に時間がかかってしまうため、
    //そのパーティクルをクラスかすることで、処理速度の向上を図っている
    auto normal = dynamic_cast<NormalCrystal*>(this);
    if(normal != NULL && creater != NULL){
        auto bParticle = BreakParticle::create();
        bParticle->setAutoRemoveOnFinish(true);
        bParticle->resetSystem();
        bParticle->setPosition(this->getPosition() + deltaVec);
        stage->addChild(bParticle);
        
        return;
    }
    
    //ノーマルクリスタルの場合以下の処理は無視される
    ParticleSystemQuad* particle = ParticleSystemQuad::create(filePath);
    particle->setAutoRemoveOnFinish(true);
    particle->resetSystem();
    particle->setPosition(this->getPosition() + deltaVec);
    
    stage->addChild(particle);
}

void Crystal::DestroyAction()
{
    auto big = ScaleTo::create(0.1f, 1.0f);
    auto fadeout = FadeOut::create(0.1f);
    auto spawn = Spawn::create(big,fadeout, NULL);
    
    auto destroy = CallFunc::create([this](){
        this->DestroyFunc();
    });
    
    auto seq = Sequence::create(spawn,destroy, NULL);
    this->runAction(seq);
}
