//
//  Wall.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include "PhysicsArea.hpp"
#include "Common.h"

bool PhysicsArea::init()
{
    if(!Node::init()) {
        return false;
    }
    
    return true;
}

PhysicsArea* PhysicsArea::create(const cocos2d::Vec2 &pos, const cocos2d::Size &size)
{
            PhysicsArea *pRet = new(std::nothrow) PhysicsArea();
            if (pRet && pRet->init())
            {
                pRet->autorelease();
                pRet->setContentSize(size);
                pRet->setPosition(pos);
    
                auto mat = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT;
                mat.restitution = WALL_RESTITUTION;
                mat.friction = 0.0f;
    
                auto pb = cocos2d::PhysicsBody::createBox(size,mat);
                pb->setCategoryBitmask(0x04);
                pb->setContactTestBitmask(0x01);
                pb->setCollisionBitmask(0x01);
                pb->setDynamic(false);
                pRet->setPhysicsBody(pb);
    
                return pRet;
            }
            else
            {
                delete pRet;
                pRet = nullptr;
                return nullptr;
            }
}
