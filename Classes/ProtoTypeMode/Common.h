//
//  Common.h
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/08.
//
//
//プロトタイプモードで共通の値をここに保管する
//また、頻繁に調整する値（ゲームの難易度に関わるようなもの）も
//ここで宣言してファイルを行ったり来たりするなどの無駄な労力にならないようにする
#ifndef Common_h
#define Common_h

//インクルードファイル
//---------------------------------
#include "Ball.hpp"
#include "Bar.hpp"
#include "BarCreater.hpp"
#include "MainScene.hpp"
#include "MainUILayer.hpp"
#include "TitleScene.hpp"
#include "Wall.hpp"
#include "Crystal.hpp"
#include "NormalCrystal.hpp"
#include "PrototypeModeManager.hpp"
#include "Stage.hpp"
#include "StageCreater.hpp"
#include "ResultScene.hpp"
#include "TimeCrystal.hpp"
#include "ExplosionCrystal.hpp"
#include "SubBall.hpp"
#include "BallCrystal.hpp"
#include "TitleStage.hpp"
#include "TitleShop.hpp"
#include "SkinSelect.hpp"
#include "AbilityStore.hpp"
#include "ConfirmationLayer.hpp"
#include "TutorialLayer.hpp"
#include "PhysicsArea.hpp"
#include "BreakParticle.hpp"

#include "AtomUtil.h"
#include "NendModule.h"
//---------------------------------

//タグ
enum class Tag{
    PLAYER,
    WALL,
    BAR,
    CRYSTAL,
    BALL
};

const float         LEFT_TIME               = 30.0f;    //残り時間の初期値

const GLubyte       GUIDEBAR_OPACITY        = 125;      //バー生成する際のガイド線の透明度
const float         MIN_BAR_LENGTH          = 80.0f;    //バーの長さの最小値これより短い長さだと生成しないようにする
const float         BAR_LIFE_TIME           = 3.0f;     //バーが生成されてから消えるまでの時間

const float         BALL_MAX_SPEED          = 2500.0f;  //ボールの最高速度
const float         BALL_MIN_SPEED          = 500.0f;   //ボールの最低速度
const float         BALL_SIZE               = 1.0f/2.0f;    //ボールの大きさ
const float         SUB_BALL_LIFETIME       = 1.0f;     //紫クリスタル壊した時に現れるサブボールの命
const float         SUB_BALL_ADD_LIFETIME   = 1.0f;     //サブボールのレベルマックス時に加算される命
const float         SUB_BALL_FIRSTSPEED     = 1000.0f;  //サブボールの最初のスピード

const float         WALL_RESTITUTION        = 0.9f;     //壁の反発係数
const float         BAR_RESTITUTION         = 5.0f;     //バーの反発係数

const float         TIME_CRYSTAL_ADD_TIME   = 0.5f;     //タイムクリスタル壊した時に増える時間の初期値
const float         EXPLOSION_RADIUS        = 100.0f;   //爆発クリスタルが爆発する時の半径の初期値
const float         TIME_CRYSTAL_ABILITY    = 0.5f;     //タイムクリスタルのレベルアップで加算される最大値
const float         EXPLOSION_ABILITY       = 150.0f;   //爆発クリスタルのレベルアップで加算される最大値

const float         MAIN2RESULT_TIME        = 2.0f;     //ゲームが終了してリザルト画面まで遷移するまでの時間

const std::string   USE_FONT_PATH           = "fonts/airstrike.ttf";

const bool          IS_LOCKEDMODE           = true;     //コンテンツにロックをかけるか

//ステージをアンロックするのに必要なハイスコア
const int STAGE_UNLOCK_SCORE[] = {
    0,
    1000,
    2000,
    3000,
    4000,
    5000,
    6000
};

//ボールをアンロックするのにかかるBP(BreakPoint)
const int BALL_FEE[] = {
  0,0,10,10,10,10,10,10,10,10
};

const int BAR_FEE[] ={
  0,0,0,0,0,10,10,10,10,10,10,10,10,10,10,10
};

//サウンドのIDを定義
//-------------------------------------
//メインキューシート
const int SE_BTC_VOICE          = 0;
const int SE_GLASS_BREAK        = 1;
const int SE_RECOVERY           = 2;
const int SE_BALL_PLUS          = 3;
const int SE_EXPLOSION          = 4;
const int SE_STAGE_CHANGE       = 5;
const int SE_BALL_BOUND         = 6;
const int SE_DESTROY            = 7;
const int SE_BUTTON_ON          = 8;
const int SE_BUTTON_OFF         = 9;
const int MS_BREAK_THE_CRYSTAL  = 10;
const int MS_START              = 11;
const int MS_BREAKER            = 12;
const int MS_ELICA              = 13;
const int MS_REFLECTIONS        = 14;
const int MS_UNTITLED           = 15;
const int MS_EMOTION            = 16;
const int MS_BTC_RESULT         = 17;

//サブキューシート
const int SE_SUB_BTC_RESULT     = 0;
const int SE_SUB_BUTTON_ON      = 1;
const int SE_SUB_BUTTON_OFF     = 2;
//-------------------------------------


#endif /* p_Common_h */
