//
//  PrototypeModeManager.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//

#include "PrototypeModeManager.hpp"

USING_NS_CC;

PrototypeModeManager* PrototypeModeManager::mPrototypeManager = NULL;

PrototypeModeManager::PrototypeModeManager()
{
    
}

PrototypeModeManager* PrototypeModeManager::getInstance()
{
    if(mPrototypeManager == NULL)
    {
        mPrototypeManager = new PrototypeModeManager();
        mPrototypeManager->initialize();
    }
    
    return mPrototypeManager;
}

void PrototypeModeManager::initialize()
{
    auto userDef = cocos2d::UserDefault::getInstance();
    
    _Score = 0;
    _BgmFirstId = 10;
    _BgmId = _BgmFirstId;
    
    _selectedBackGround = 0;
    _particlePath.push_back("particle/BackGround/Space.plist");
    _particlePath.push_back("particle/BackGround/start.plist");
    _particlePath.push_back("particle/BackGround/breaker.plist");
    _particlePath.push_back("particle/BackGround/MainBack3.plist");
    _particlePath.push_back("particle/BackGround/reflections.plist");
    _particlePath.push_back("particle/BackGround/untitled.plist");
    _particlePath.push_back("particle/BackGround/emotion.plist");
    
    _selectedBall = userDef->getIntegerForKey("selectedBall",0);
    _ballTexturePath.push_back("Texture/Ball/Ball.png");
    _ballTexturePath.push_back("Texture/Ball/Ball2.png");
    _ballTexturePath.push_back("Texture/Ball/Ball3.png");
    _ballTexturePath.push_back("Texture/Ball/Ball4.png");
    _ballTexturePath.push_back("Texture/Ball/Ball5.png");
    _ballTexturePath.push_back("Texture/Ball/Ball6.png");
    _ballTexturePath.push_back("Texture/Ball/Ball7.png");
    _ballTexturePath.push_back("Texture/Ball/Ball8.png");
    _ballTexturePath.push_back("Texture/Ball/Ball9.png");
    _ballTexturePath.push_back("Texture/Ball/Ball10.png");
    
    _selectedBar = userDef->getIntegerForKey("selectedBar",0);
    _barTexturePath.push_back("Texture/Bar/Bar2.png");
    _barTexturePath.push_back("Texture/Bar/Bar3.png");
    _barTexturePath.push_back("Texture/Bar/Bar4.png");
    _barTexturePath.push_back("Texture/Bar/Bar5.png");
    _barTexturePath.push_back("Texture/Bar/Bar6.png");
    _barTexturePath.push_back("Texture/Bar/Bar7.png");
    _barTexturePath.push_back("Texture/Bar/Bar8.png");
    _barTexturePath.push_back("Texture/Bar/Bar9.png");
    _barTexturePath.push_back("Texture/Bar/Bar10.png");
    _barTexturePath.push_back("Texture/Bar/Bar11.png");
    _barTexturePath.push_back("Texture/Bar/Bar12.png");
    _barTexturePath.push_back("Texture/Bar/Bar13.png");
    _barTexturePath.push_back("Texture/Bar/Bar14.png");
    _barTexturePath.push_back("Texture/Bar/Bar15.png");
    _barTexturePath.push_back("Texture/Bar/Bar16.png");
    _barTexturePath.push_back("Texture/Bar/Bar17.png");
    
    
    _stageTexturePath.push_back("Texture/Stage/StageBase2.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase3.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase4.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase5.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase6.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase7.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase8.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase9.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase10.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase11.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase12.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase13.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase14.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase15.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase16.png");
    _stageTexturePath.push_back("Texture/Stage/StageBase17.png");
}

void PrototypeModeManager::MultiResolution(Vec2& origin, Size& visible)
{
    auto target = Application::getInstance()->getTargetPlatform();
    
    origin = Director::getInstance()->getVisibleOrigin();
    visible = Director::getInstance()->getVisibleSize();
    
    //iPadの場合横幅が広いので壁を内側に寄せる
    if(target == ApplicationProtocol::Platform::OS_IPAD){
        origin.x += 64.0f;
        visible.width -= 128.0f;
    }
}

int* PrototypeModeManager::CopyArray(const int array[])
{
    int size = sizeof(array) / sizeof(array[0]);
    
    int result[size];
    
    for(int i = 0; i < size; i++)
    {
        result[i] = array[i];
    }
    
    return result;
}
