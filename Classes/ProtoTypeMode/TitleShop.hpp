//
//  TitleShop.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/23.
//
//

#ifndef TitleShop_hpp
#define TitleShop_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "SkinSelect.hpp"
#include "AbilityStore.hpp"

//モーダルレイヤー
/**
 *@class TitleShop
 *@brief スキン購入選択、レベルアップすることができるショップ
 */
class TitleShop : public cocos2d::LayerColor
{
private:
    ///タッチされた瞬間呼ばれる
    bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
    ///タッチしている間呼ばれる
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    ///指を離した瞬間呼ばれる
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    ///戻るボタンを押した時に呼ばれる
    void onBackButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    ///スキンとアビリティを切り替えるトグルボタンが押された時に呼ばれる
    void onToggleChanged(Ref *pSender,cocos2d::ui::Widget::TouchEventType type);
    ///トグルのどちらが選択されているか
    ///false スキンセレクト
    ///true　アビリティショップ
    bool _isToggleOn;
    ///BP残高を表示するラベル
    cocos2d::Label* _moneyLabel;
    ///スキンセレクトレイヤー
    SkinSelect* _skinSelect;
    ///アビィティショップレイヤー
    AbilityStore* _abilityStore;
public:
    bool init();
    
    CREATE_FUNC(TitleShop);
    
    void setMoneyLabel();
    

};

#endif /* TitleShop_hpp */
