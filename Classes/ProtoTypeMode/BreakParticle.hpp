//
//  BreakParticle.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/04/24.
//
//

#ifndef BreakParticle_hpp
#define BreakParticle_hpp

#include <stdio.h>
#include <cocos2d.h>

class BreakParticle : public cocos2d::ParticleSystemQuad{
public:
    bool init();
    CREATE_FUNC(BreakParticle);
};

#endif /* BreakParticle_hpp */
