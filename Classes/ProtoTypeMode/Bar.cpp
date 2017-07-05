//
//  Bar.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include "Common.h"

USING_NS_CC;

bool Bar::init(const float length,const cocos2d::Vec2 pos,const float rotation)
{
    auto manager = PrototypeModeManager::getInstance();
    
    auto textureCache = Director::getInstance()->getTextureCache();
    Texture2D* barTexture = textureCache->getTextureForKey(manager->_barTexturePath.at(manager->_selectedBar));
    
    if(!Sprite::initWithTexture(barTexture))
        return false;
    
    this->scheduleUpdate();
    
    initPhysicsBody();
    
    barAction();
    
    this->setPosition(pos);
    this->setRotation(rotation);
    this->setScale(length/this->getContentSize().width,0.5f);
    this->setTag((int)Tag::BAR);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Bar::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

Bar* Bar::create(const float length,const cocos2d::Vec2 pos,const float rotation)
{
    
    Bar *pRet = new(std::nothrow) Bar();
    if (pRet && pRet->init(length,pos,rotation))
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

void Bar::initPhysicsBody()
{
    auto cSize = this->getContentSize();
    
    auto mat = PHYSICSBODY_MATERIAL_DEFAULT;
    mat.restitution = BAR_RESTITUTION;
    mat.friction = 0.0f;
    
    auto pb = PhysicsBody::createBox(Size(cSize.width,cSize.height/6.0f),mat);
    pb->setCategoryBitmask(0x02);
    pb->setContactTestBitmask(0x01);
    pb->setCollisionBitmask(0x01);
    pb->setDynamic(false);
    
    this->setPhysicsBody(pb);
}

void Bar::barAction()
{
    auto fadeOut = FadeOut::create(BAR_LIFE_TIME);
    auto destroy = CallFunc::create([this](){
        this->removeFromParentAndCleanup(true);
    });
    
    auto seq = Sequence::create(fadeOut, destroy,nullptr);
    this->runAction(seq);
}

bool Bar::onContactBegin(PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    auto own = dynamic_cast<Bar*>(nodeA);
    if(!own){
        own = dynamic_cast<Bar*>(nodeB);
    }
    
    auto ball = dynamic_cast<Ball*>(nodeA);
    if(!ball){
        ball = dynamic_cast<Ball*>(nodeB);
    }
    
    if(!ball || own != this){
        return true;
    }
    
    //ボールと当たったらバーを消滅させる
    if(ball){
        if(this->getNumberOfRunningActions() == 1)
        {
            criadx2le::playCueById(SE_DESTROY);
            
            //ボールが衝突してからスケールが０になるまでにかかる時間
            float smallTime = 0.2f;
            
            auto small = ScaleTo::create(smallTime, 0.0f, this->getScaleY());
            auto destroy = CallFunc::create([this](){
                this->removeFromParentAndCleanup(true);
            });
            auto seq = Sequence::create(small,destroy, NULL);
            this->runAction(seq);
        }
    }
    
    return true;
}
