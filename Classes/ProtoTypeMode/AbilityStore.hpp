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
 *@brief レベルアップする
 */
class AbilityStore : public cocos2d::Layer
{
private:
    ///アビリティのレベルを表示するラベル
    cocos2d::Label* _level[4];
    ///アビリティのレベルを上げるボタン
    cocos2d::ui::Button* _abilityBt[4];
    /**
     *@brief レベルのラベルのテキストを設定する
     *@param index _level[index]
     */
    void setLevelLabelString(int index);
    /**
     *@brief レベルボタンを押せるものは押せるように
     *       押せないものは押せないように設定する
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
