//
//  Stage.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/09.
//
//

#ifndef Stage_hpp
#define Stage_hpp

#include <cocos2d.h>

/**
 *@class Stage
 *@brief メインシーンで使用される壁枠のクラス
 */
class Stage : public cocos2d::Sprite
{
private:
    /**
     *@brief ステージが生成される時に再生するアクションを設定
     */
    void initAction();
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(Stage);
    ///クリスタルを追加するためのノード
    cocos2d::SpriteBatchNode* _crystalBatch;
};

#endif /* Stage_hpp */
