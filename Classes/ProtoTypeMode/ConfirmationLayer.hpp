//
//  ConfirmationLayer.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/27.
//
//

#ifndef ConfirmationLayer_hpp
#define ConfirmationLayer_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
/**
 *@class ConfirmationLayer
 *@brief 購入確認レイヤー
 */
class ConfirmationLayer : public cocos2d::LayerColor
{
private:
    ///タッチされた瞬間に呼ばれる
    bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
    ///タッチしている間呼ばれる
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    ///指が話された瞬間に呼ばれる
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    ///タッチのイベントリスナー
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    ///YESボタンが押された時に呼ばれる
    void onYesButton(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    ///NOボタンが押された時に呼ばれる
    void onNoButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    ///YESボタンが押された時に実行する購入処理のラムダ式
    std::function<void()> _parchaceFunc;
public:
    /**
     *@brief 初期化関数
     *@param func 購入処理が書かれたラムダ式
     *@return true 初期化成功
     *@return false 初期化失敗
     */
    bool init(std::function<void()> func);
    /**
     *@brief create関数
     *@param func 購入処理が書かれたラムダ式
     *@return 作成された確認レイヤー
     */
    static ConfirmationLayer* create(std::function<void()> func);
};

#endif /* ConfirmationLayer_hpp */
