//
//  Ball.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//
#include "Common.h"

USING_NS_CC;

bool Ball::init(SpriteBatchNode* _batch)
{
    auto userDef = UserDefault::getInstance();
    if(!Sprite::initWithTexture(_batch->getTexture()))
        return false;
    
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    //PhysicsMaterialを設定
    auto mat = PHYSICSBODY_MATERIAL_DEFAULT;
    mat.restitution = 1.0f;
    mat.friction = 0.0f;
    
    
    auto pb = PhysicsBody::createCircle(this->getContentSize().width/2,mat);
    
    pb->setCategoryBitmask(0x01);
    pb->setContactTestBitmask(0x0e);
    pb->setCollisionBitmask(0x06);
    
    pb->setRotationEnable(false);
    pb->setMass(1.0f);
    
    this->setPhysicsBody(pb);

    //大きさ
    auto level = userDef->getIntegerForKey("ability0",1);
    this->setScale(BALL_SIZE+((0.5*level)/10.0f));
    this->setTag((int)Tag::BALL);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Ball::onContactBegin,this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

Ball* Ball::create(SpriteBatchNode* _batch)
{
    Ball *pRet = new(std::nothrow) Ball();
    if (pRet && pRet->init(_batch))
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

//衝突検出
bool Ball::onContactBegin(cocos2d::PhysicsContact &contact){
    
    if(contact.getShapeA()->getBody()->getNode() != this) {
        return true;
    }
    
    auto shapeB = contact.getShapeB();
    
    auto wall = dynamic_cast<PhysicsArea*>(shapeB->getBody()->getNode());
    
    if(wall) {
        if(wall->getTag() == (int)Tag::WALL) {
            auto pb = this->getPhysicsBody();
            
            //ボールの速さによって音の大きさと高さを変更
            ///////////////////////////////////////////////////////////////////////////////////////
            CriFloat32 aisac = pb->getVelocity().getLength() / (BALL_MAX_SPEED - BALL_MIN_SPEED);
            
            if(aisac >= 1.0f)
                aisac = 1.0f;
            else if(aisac <= 0)
                aisac = 0.0f;
            
            criadx2le::setAisac(0, aisac);
            criadx2le::playCueById(SE_BALL_BOUND);
            ///////////////////////////////////////////////////////////////////////////////////////
            
            auto parent = this->getParent();
            
            //壁に当たった時パーティクル発生させる
            ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/Collision.plist");
            particle->setAutoRemoveOnFinish(true);
            particle->resetSystem();
            particle->setPosition(this->getPosition()+pb->getVelocity().getNormalized()*60);
            parent->addChild(particle,9);
        }
    }
    
    return true;
}

void Ball::BallMove(const cocos2d::Vec2 Vec){
    Vec2 MoveVelo = Vec * BALL_MAX_SPEED;
    this->getPhysicsBody()->applyImpulse(MoveVelo);
}

//ボールの速度が最高速度と最低速度の間になるようにする処理
//壁からはみ出さないようにする処理が書かれている
void Ball::update(float delta){
    
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    Vec2 nowD = this->getPhysicsBody()->getVelocity();
    
    if( nowD.length() > (Vec2::ONE.getNormalized()*BALL_MAX_SPEED).length())
    {
        nowD.normalize();
        this->getPhysicsBody()->setVelocity(nowD*BALL_MAX_SPEED);
    }
    
    else if(nowD.length()< (Vec2::ONE.getNormalized()*BALL_MIN_SPEED).length()){
        nowD.normalize();
        this->getPhysicsBody()->setVelocity(nowD*BALL_MIN_SPEED);
    }
    
    Vec2 nowPos = getPosition();
    float wallWidth = 60;
    
    if(nowPos.x < origin.x){
        float out = origin.x - nowPos.x;
        setPosition(nowPos.x + out + wallWidth, nowPos.y);
        Vec2 nowVel = this->getPhysicsBody()->getVelocity();
        nowVel.x *= -1.0f;
        this->getPhysicsBody()->setVelocity(nowVel);
    }
    if(nowPos.x > origin.x + vs.width){
        float out = nowPos.x - (origin.x + vs.width);
        setPosition(nowPos.x - out - wallWidth, nowPos.y);
        Vec2 nowVel = this->getPhysicsBody()->getVelocity();
        nowVel.x *= -1.0f;
        this->getPhysicsBody()->setVelocity(nowVel);
    }
    
    if(nowPos.y > origin.y + vs.height){
        float out = nowPos.y - (origin.y + vs.height);
        setPosition(nowPos.x, nowPos.y - out - wallWidth);
        Vec2 nowVel = this->getPhysicsBody()->getVelocity();
        nowVel.y *= -1.0f;
        this->getPhysicsBody()->setVelocity(nowVel);
    }
    if(nowPos.y < origin.y){
        float out = origin.y - nowPos.y;
        setPosition(nowPos.x, nowPos.y + out + wallWidth);
        Vec2 nowVel = this->getPhysicsBody()->getVelocity();
        nowVel.y *= -1.0f;
        this->getPhysicsBody()->setVelocity(nowVel);
    }
    
}



