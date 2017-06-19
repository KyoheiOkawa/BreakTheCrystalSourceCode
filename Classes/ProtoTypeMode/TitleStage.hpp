//
//  TitleStage.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/22.
//
//

#ifndef TitleStage_hpp
#define TitleStage_hpp

#include <cocos2d.h>

/**
 *@class TitleStage
 *@brief 曲、ステージを選択するクラス
 *左右のフリックでページをめくるように選択できる
 */
class TitleStage : public cocos2d::Layer
{
private:
    ///タッチ開始した時に呼ばれる
    bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
    ///タッチしている間呼ばれる
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    ///指を離した瞬間に呼ばれる
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    /**
     *@brief 選ばれているステージと前後のステージのパーティクルを
     *再生しておく関数
     */
    void changeSelect();
    
    ///背景パーティクルを追加するためのノード
    cocos2d::Node* _particleNode;
    ///背景パーティクル
    cocos2d::Vector<cocos2d::ParticleSystemQuad*> _backParticle;
    ///横フリックでステージを選択するとき
    ///フリックする長さが足りなかった場合に
    ///パーティクルを追加するためのノードを
    ///元の位置に戻す際に使用する変数
    cocos2d::Vec2 _parNodeBeforePos;
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(TitleStage);
    ///選ばれているステージのナンバー
    int _selectedNum;
    /**
     *@brief ステージがアンロックされているか確認する関数
     *@param i ステージのナンバー
     *@return アンロックされている場合true
     */
    bool JudgeIsLocked(int i);
};

#endif /* TitleStage_hpp */
