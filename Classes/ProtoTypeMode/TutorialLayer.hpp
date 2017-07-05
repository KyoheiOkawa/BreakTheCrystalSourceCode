//
//  TutorialLayer.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/28.
//
//

#ifndef TutorialLayer_hpp
#define TutorialLayer_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
/**
 *@class TutorialLayer
 *@brief 遊び方のスライドを表示するレイヤー
 */
class TutorialLayer : public cocos2d::LayerColor
{
private:
    /**
     *@brief 戻るボタン（←）が押された時に呼ばれ、このレイヤーを閉じる
     *@param[in] pSender メッセージを送ったオブジェクト
     *@param[in] type タッチイベントのタイプ
     */
    void onBackButton(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
    ///このレイヤーがタッチされた時に呼ばれる
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(TutorialLayer);
};

#endif /* TutorialLayer_hpp */
