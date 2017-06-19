//
//  PrototypeModeManager.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//シングルトンクラス
//プロトタイプモードのゲームマネージャー
#ifndef PrototypeModeManager_hpp
#define PrototypeModeManager_hpp

#include <cocos2d.h>

class PrototypeModeManager
{
private:
    ///コンストラクタ
    PrototypeModeManager();
    ///唯一存在するインスタンス
    static PrototypeModeManager* mPrototypeManager;
    
public:
    /**
     *@brief インスタンス取得
     *@return PrototypeModeManagerのインスタンス
     */
    static PrototypeModeManager* getInstance();
    /**
     *@brief 配列コピー関数
     *@param array[] コピーしたい配列のポインタ
     *@return コピー後の配列のポインタ
     */
    static int* CopyArray(const int array[]);
    ///初期化関数
    void initialize();
    
    /**
     *@brief マルチ解像度対応クラス
     *@param[out] origin スクリーン座標の原点の座標
     *@param[out] visible スクリーン座標の幅、高さのサイズ
     */
    static void MultiResolution(cocos2d::Vec2& origin, cocos2d::Size& visible);
    ///メインゲームでのスコア
    unsigned long _Score;
    ///バックグラウンドパーティクルのパス
    std::vector<std::string> _particlePath;
    ///ボールテクスチャのパス
    std::vector<std::string> _ballTexturePath;
    ///バーテクスチャのパス
    std::vector<std::string> _barTexturePath;
    ///ステージの枠のテクスチャのパス
    std::vector<std::string> _stageTexturePath;
    
    ///選択されたバックグラウンドパーティクルの番号
    int _selectedBackGround;
    ///キューシートのBGMの先頭のID
    int _BgmFirstId;
    ///再生するBGMのID
    int _BgmId;
    
    ///選択されたボールの番号
    int _selectedBall;
    ///選択されたバー（壁枠）の番号
    int _selectedBar;
};

#endif /* PrototypeModeManager_hpp */
