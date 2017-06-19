//
//  MainUILayer.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/07.
//
//

#ifndef MainUILayer_hpp
#define MainUILayer_hpp

#include <cocos2d.h>
#include <ui/CocosGUI.h>

/**
 *@class MainUILayer
 *@brief メインシーンで使用するUI用のレイヤークラス
 */
class MainUILayer : public cocos2d::Layer
{
private:
    ///残り時間のラベル
    cocos2d::Label* _time;
    ///壊したクリスタルの数のラベル
    cocos2d::Label* _broken;
    ///ポーズボタン
    cocos2d::ui::Button* _pauseBt;
    ///FlickToStartのラベル
    cocos2d::Label* _StartEnd;
    ///ポーズボタン押した時に表示されるパネル
    cocos2d::LayerColor* _pausePanel;
    ///再開ボタン
    cocos2d::ui::Button* _panelResume;
    ///リトライボタン
    cocos2d::ui::Button* _panelRetry;
    ///タイトルへ戻るボタン
    cocos2d::ui::Button* _panelReturn;
    
    /**
     *@brief ノードを追加
     */
    void Hierarchy();
    /**
     *@brief            アップデート関数
     *@param delta　１フレームにかかる時間
     */
    void update(float delta) override;
    /**
     *@brief            ポーズボタンを押した時に呼ばれる関数
     *@param *pSender   イベントメッセージを送ったオブジェクトの情報
     *@param type       タッチイベントのタイプ
     */
    void onPauseButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief            ポーズメニューの再開ボタンを押した時に呼ばれる関数
     *@param *pSender   イベントメッセージを送ったオブジェクトの情報
     *@param type       タッチイベントのタイプ
     */
    void onResumeButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief            ポーズメニューのリトライボタンを押した時に呼ばれる関数
     *@param *pSender   イベントメッセージを送ったオブジェクトの情報
     *@param type       タッチイベントのタイプ
     */
    void onRetryButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief            ポーズメニューのリターンボタンを押した時に呼ばれる関数
     *@param *pSender   イベントメッセージを送ったオブジェクトの情報
     *@param type       タッチイベントのタイプ
     */
    void onReturnButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
public:
    /**
     *@brief            初期化関数
     *@return           初期化成功の場合true
     */
    bool init() override;
    ///create関数マクロ
    CREATE_FUNC(MainUILayer);
};

#endif /* MainUILayer_hpp */
