//
//  AbilityStore.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/25.
//
//

#ifndef AbilityStore_hpp
#define AbilityStore_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"

/**
 *@class AbilityStore
 *@brief レベルアップするショップのレイヤー
 */
class AbilityStore : public cocos2d::Layer
{
private:
    ///アビリティのレベルを表示するラベル
    cocos2d::Label* _level[4];
    ///アビリティのレベルを上げるボタン
    cocos2d::ui::Button* _abilityBt[4];
    /**
     *@brief レベルのラベルのテキストを更新する
     *@param[in] index 更新したい_level変数のid(_level[index])
     */
    void setLevelLabelString(int index);
    /**
     *@brief レベルボタンを押せるものは押せるように、押せないものは押せないように設定する
     *
     *レベルマックス、残金不足の時に押せなくなる
     *
     */
    void setLevelBtTouchEnable();
    ///レベルアップボタンが押された時に呼ばれる
    void onAbilityButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(AbilityStore);
};

#endif /* AbilityStore_hpp */
