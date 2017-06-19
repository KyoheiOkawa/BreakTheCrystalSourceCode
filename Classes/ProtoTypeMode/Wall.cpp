//
//  Wall.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include "Common.h"

USING_NS_CC;

bool Wall::init()
{
    if(!Node::init())
        return false;
    
    auto manager = PrototypeModeManager::getInstance();
    
    Vec2 origin;
    Size vs;
    
    manager->MultiResolution(origin, vs);
    
    auto vWallSize = Size(60,vs.height);
    auto hWallSize = Size(vs.width,vWallSize.width);
    auto topWallSize = Size(vs.width,160);
    
    auto wallL = PhysicsArea::create(origin, vWallSize);
    this->addChild(wallL);
    wallL->setTag((int)Tag::WALL);
    
    auto wallR = PhysicsArea::create(origin+Vec2(vs.width-vWallSize.width,0),vWallSize);
    this->addChild(wallR);
    wallR->setTag((int)Tag::WALL);
    
    auto wallU = PhysicsArea::create(origin,hWallSize);
    this->addChild(wallU);
    wallU->setTag((int)Tag::WALL);
    
    auto wallT = PhysicsArea::create(origin+Vec2(0,vs.height-topWallSize.height),topWallSize);
    this->addChild(wallT);
    wallT->setTag((int)Tag::WALL);
    
    return true;
}
