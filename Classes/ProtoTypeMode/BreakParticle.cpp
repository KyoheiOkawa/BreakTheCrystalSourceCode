//
//  BreakParticle.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/04/24.
//
//

#include "BreakParticle.hpp"

bool BreakParticle::init(){
    int maxParticles = 80;
    
    if(!initWithTotalParticles(maxParticles))
        return false;
    
    _angle = -2.0f;
    _angleVar = 180.0f;
    
    _duration = 0.2f;
    
    _blendFunc.src = 770;
    _blendFunc.dst = 1;
    
    _startColor.r = 0.4f;
    _startColor.g = 0.88f;
    _startColor.b = 0.88f;
    _startColor.a = 0.2f;
    
    _startColorVar.r = 0.0f;
    _startColorVar.g = 0.0f;
    _startColorVar.b = 0.0f;
    _startColorVar.a = 0.2f;
    
    _endColor.r = 0.4f;
    _endColor.g = 0.88f;
    _endColor.b = 0.88f;
    _endColor.a = 0.2f;
    
    _endColorVar.r = 0.0f;
    _endColorVar.g = 0.0f;
    _endColorVar.g = 0.0f;
    _endColorVar.a = 0.1f;
    
    _startSize = 9.0f;
    _startSizeVar = 11.0f;
    _endSize = 2.0f;
    _endSizeVar = 0.0f;
    
    setPosition(357.0f,684.0f);
    _posVar.x = 0.0f;
    _posVar.y = 0.0f;
    
    _startSpin = -265.0f;
    _startSpinVar = 0.0f;
    _endSpin = 0.0f;
    _endSpinVar = 0.0f;
    
    _emitterMode = Mode::GRAVITY;
    
    modeA.gravity.x = 0.0f;
    modeA.gravity.y = -358.0f;
    
    modeA.speed = 350.0f;
    modeA.speedVar = 174.0f;
    
    modeA.radialAccel = 0.0f;
    modeA.radialAccelVar = 0.0f;
    
    modeA.tangentialAccel = 0.0f;
    modeA.tangentialAccelVar = 0.0f;
    
    modeA.rotationIsDir = false;
    
    _life = 0.1f;
    _lifeVar = 0.15f;
    
    _emissionRate = _totalParticles / _life;
    
    _opacityModifyRGB = false;
    
    std::string textureName = "particle/Break2.png";
    
    setTexture(cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(textureName));
    
    return true;
}
