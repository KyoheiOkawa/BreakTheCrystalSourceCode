//
//  MainScene.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <cocos2d.h>


/**
 *@enum GameState
 *@brief ゲーム進行の状態
 */
enum GameState{
    START,      ///ゲームがスタートしていない状態
    PLAYING,    ///ゲームがスタートしている状態
    END,        ///ゲームが終わっている状態
    POSE        ///ポーズ状態
};

/**
 *@class MainScene
 *@brief メインシーン
 */
class MainScene : public cocos2d::LayerColor
{
private:
    ///ゲームの状態
    GameState _state;
    ///残り時間
    float _leftTime;
    ///壊したクリスタルの総数
    unsigned long _destroyedCrystals;
    ///最後の３カウントを表示させることに用いるラベル
    cocos2d::Label* _last3Count;
    
    /**
     @brief             ノードを追加する
     */
    void AddNode();
    /**
     @brief             テクスチャキャッシュにテクスチャを読み込む
     */
    void LoadTextureCache();
    /**
     @brief             アップデート関数
     */
    void update(float delta) override;
    /**
     *@brief            ゲーム開始前の状態の時に毎フレーム実行する関数
     */
    void StartFunc();
    /**
     *@brief            ゲーム中の状態に毎フレーム実行する関数
     *@param delta      １フレームにかかった時間
     */
    void PlayingFunc(float delta);
    /**
     *@brief            ポーズ状態の時に毎フレーム実行する関数
     */
    void PoseFunc();
    /**
     *@brief            ゲーム終了状態の時に毎フレーム実行する関数
     */
    void EndFunc();
    /**
     *@brief            タッチした瞬間に呼ばれる関数
     *@param cocos2d::Touch* touch
     *@param cocos2d**Event* event
     *@return           常にtrue
     */
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    /**
     *@brief            タッチしている間呼ばれる関数
     *@param cocos2d::Touch* touch
     *@param cocos2d**Event* event
     */
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    /**
     *@brief            指が話された瞬間に呼び出される関数
     *@param cocos2d::Touch* touch
     *@param cocos2d**Event* event
     */
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
public:
    /**
     *@brief            メインシーン作成
     *@return           メインシーンのインスタンス
     */
    static cocos2d::Scene* createScene();
    /**
     *@brief            初期化関数
     */
    bool init() override;
    ///create関数マクロ
    CREATE_FUNC(MainScene);
    /**
     *@breif            ゲームステートの取得
     *@return           ゲームステート
     */
    GameState GetState() { return _state;}
    /**
     *@brief            残り時間の取得
     *@return           残り時間
     */
    float GetTime() { return _leftTime;}
    /**
     *@brief            壊したクリスタルの数を取得
     *@return           壊したクリスタルの数
     */
    unsigned long GetBrokenCrystalsCount() {return _destroyedCrystals;}
    /**
     *@brief            壊したクリスタルの総数に１を加算する
     */
    void AddBrokenCrystalCount();
    /**
     *@brief            残り時間に加算する
     *@param  time      加算したい時間(sc)
     */
    void AddTime(float time);
    
public:
    ///サブボールを追加するノード
    cocos2d::SpriteBatchNode* _BallBatch;

};

#endif /* MainScene_hpp */
