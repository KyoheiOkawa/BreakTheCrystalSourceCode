//
//  StageCreater.hpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/09.
//
//

#ifndef StageCreater_hpp
#define StageCreater_hpp

#include <cocos2d.h>

/**
 *@enum CrystalType
 *@brief クリスタルの種類
 */
enum CrystalType{
    NORMAL,
    TIME,
    BALL,
    EXPLOSION
};

///クリスタルの行数
const int ROW = 24;
///クリスタルの列数
const int COL = 14;

/**
 *@class StageCreater
 *@brief ステージ(壁枠とクリスタル）を生成するクラス
 */
class StageCreater : public cocos2d::Layer
{
private:
    ///ステージにアクセスするためのポインタ
    Stage* _stage;
    ///選択したクリスタルを保管しておく変数
    int _Selected[ROW][COL];
    /**
     *@brief クリスタルの並び順をランダムに決定する
     *
     *決定された並び順は_Selected変数に保管される
     *
     *@param[in] isFirstSelect ゲーム開始時に並べる時はtrueを設定する
     */
    inline void SelectCrystals(bool isFirstSelect);
public:
    ///初期化関数
    bool init();
    ///create関数マクロ
    CREATE_FUNC(StageCreater);
    ///アップデート関数
    void update(float delta);
    /**
     *@brief ステージにクリスタルを並べる関数
     */
    inline void createCrystals();
};

#endif /* StageCreater_hpp */
