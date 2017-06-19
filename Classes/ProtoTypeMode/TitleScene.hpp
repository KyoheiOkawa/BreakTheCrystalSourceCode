//
//  TitleScene.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

#include <cocos2d.h>
#include "ui/CocosGUI.h"

/**
 *@class TitleScene
 *@brief タイトルシーン
 */
class TitleScene : public cocos2d::LayerColor
{
private:
    /**
     *@brief ノードを追加
     */
    void Hierarchy();
    /**
     *@brief スタートボタンを押した時に呼ばれる
     */
    void onPlayButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief BPショップボタンを押した時に呼ばれる
     */
    void onShoppingButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief ランキングボタンを押した時に呼ばれる
     */
    void onRankingButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    /**
     *@brief HowToPlayボタンを押した時に呼ばれる
     */
    void onTutorialButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type);
    ///背景パーティクルを表示するレイヤー
    cocos2d::Layer* _backGround;
    ///スタートボタン
    cocos2d::ui::Button* _playButton;
    ///スタートボタンの上のラベル
    cocos2d::ui::Button* _playLabel;
public:
    /**
     *@brief シーン作成関数
     *@return 作成したシーンのポインタ
     */
    static cocos2d::Scene* createScene();
    /**
     *@brief 初期化関数
     */
    bool init();
    ///create関数マクロ
    CREATE_FUNC(TitleScene);
    /**
     *@brief スタートボタンのポインタを取得
     *@return スタートボタンのポインタ
     */
    cocos2d::ui::Button* GetPlayButton(){
        return _playButton;
    }
    /**
     *@brief スタートボタンの上のラベルのポインタを取得
     *@return スタートボタンの上のラベルのポインタ
     */
    cocos2d::ui::Button* GetPlayLabel(){
        return _playLabel;
    }
};

#endif /* TitleScene_hpp */
