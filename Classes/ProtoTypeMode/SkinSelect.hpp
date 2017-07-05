//
//  SkinSelect.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/24.
//
//

#ifndef SkinSelect_hpp
#define SkinSelect_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"
/**
 *@class SkinSelect
 *@brief スキンを選択、購入する
 */
class SkinSelect : public cocos2d::ui::ScrollView
{
private:
    ///ボールのラジオボタンが押された時に呼ばれる
    void onChangedRadioButtonSelectBall(Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
    ///バーのラジオボタンが押された時に呼ばれる
    void onChangedRadioButtonSelectBar(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief ボールがアンロックされているか確認する
     *@param[in] ballId アンロックされているか確認したいボールのID
     *@return true アンロックされている時
     *@return false ロックされている時
     */
    bool isUnlockedBall(int ballId);
    /**
     *@brief バーがアンロックされているか確認する
     *@param[in] barId アンロックされているか確認したいバーのID
     *@return true アンロックされている時
     *@return false ロックされている時
     */
    bool isUnlockedBar(int barId);
    /**
     *@brief BP不足で買えないボールのボタンを押せなくする
     */
    void setRadioButtonTouchEnableBall();
    /**
     *@brief BP不足で買えないバーのボタンを押せなくする
     */
    void setRadioButtonTouchEnableBar();
    
    ///ボールのラジオボタングループ
    cocos2d::ui::RadioButtonGroup* _radioButtonGroupBall;
    ///バーのラジオボタングループ
    cocos2d::ui::RadioButtonGroup* _radioButtonGroupBar;
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(SkinSelect);
};

#endif /* SkinSelect_hpp */
