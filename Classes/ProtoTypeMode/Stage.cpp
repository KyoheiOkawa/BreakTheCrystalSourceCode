//
//  Stage.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/09.
//
//

#include "Common.h"

USING_NS_CC;

bool Stage::init()
{
    auto manager = PrototypeModeManager::getInstance();
    
    Texture2D* texture = Director::getInstance()->getTextureCache()->getTextureForKey(manager->_stageTexturePath.at(manager->_selectedBar));
    if(!Sprite::initWithTexture(texture))
        return false;
    
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    this->setPosition(origin+vs/2+Vec2(0,-60));
    
    _crystalBatch = SpriteBatchNode::create("Texture/Crystal/Crystal2.png");
    this->addChild(_crystalBatch);
    
    initAction();
    
    return true;
}

//ステージ生成時のアクション
void Stage::initAction()
{
    criadx2le::playCueById(SE_STAGE_CHANGE);
    this->setScale(2.0f);
    
    auto wait = DelayTime::create(0.0f);
    auto shrink = ScaleTo::create(0.3f, 1.0f);
    auto seq = Sequence::create(wait,shrink, NULL);
    this->runAction(seq);
}
