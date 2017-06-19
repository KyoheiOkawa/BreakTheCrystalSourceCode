//
//  ResultScene.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/10.
//
//

#ifndef ResultScene_hpp
#define ResultScene_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"

/**
 *@class ResultScene
 *@brief リザルトシーン
 */
class ResultScene : public cocos2d::LayerColor
{

public:
    ///リザルトシーン作成
    static cocos2d::Scene* createScene();
    ///初期化関数
    virtual bool init();
    ///create関数マクロ
    CREATE_FUNC(ResultScene);
    ///タイトルに戻る
    ///タイトルボタンが押された時の呼ばれる
    void onTitleButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    ///リトライする
    ///リトライボタンが押された時に呼ばれる
    void onRetryButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    ///ツイッターのシェアボタンの処理
    void onTwitterButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    ///フェイスブックのシェアボタンの処理
    void onFaceBookButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* ResultScene_hpp */
