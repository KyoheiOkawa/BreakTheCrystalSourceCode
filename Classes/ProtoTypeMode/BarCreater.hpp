//
//  BarCreater.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef BarCreater_hpp
#define BarCreater_hpp

#include <cocos2d.h>

/**
 *@class BarCreater
 *@brief バー生成クラス
 */
class BarCreater : public cocos2d::Layer
{
public:
    /**
     *@brief                 初期化関数
     */
    bool init() override;
    
    ///create()関数マクロ
    CREATE_FUNC(BarCreater);
    
private:
    /**
     *@brief                 スクリーンをタッチした時に呼ばれるイベント
     *@return                常時true
     */
    bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event);
    /**
     *@brief                 スクリーンをタッチしている間に呼ばれるイベント
     */
    void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event);
    /**
     *@brief                 スクリーンから指を離した時に呼ばれる関数
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    /**
     *@brief                 バーのガイドを表示
     *@param[in]  touch      タッチ情報
     */
    void setGuideBar(cocos2d::Touch* touch);
    /**
     *@brief                 タッチ情報を元にバーを生成する
     *@param[in]  touch      タッチ情報
     */
    void createBar(cocos2d::Touch* touch);
    
    /**
     *@brief                 バーが壁の中に収まるように座標を補正する関数
     *@param[out]  pos        補正する座標(Vec2)
     */
    void limitBarCreateArea(cocos2d::Vec2& pos);
    /**
     *@brief                 生成するバーの長さ、位置、角度を求める関数
     *@param[out]  &length    長さの計算結果を格納する変数
     *@param[out]  &pos       位置の計算結果を格納する変数
     *@param[out]  &rotation  角度の計算結果を格納する変数
     *@param[in]  *touch     指が話された時のタッチ情報
     */
    void calBarLenPosRot(float& length,cocos2d::Vec2& pos, float& rotation,cocos2d::Touch* touch);
    /**
     *@brief                 バーの長さが最低の長さ以上に到達しているか判定する関数
     *@param[in]  length     判定する長さ
     *@return     true       到達していた場合
     *@return     false      到達していなかった場合
     */
    bool isReachedMinLength(float length);
    
    ///バーを生成する際のガイド線
    cocos2d::Sprite* _guideBar;
};

#endif /* BarCreater_hpp */
