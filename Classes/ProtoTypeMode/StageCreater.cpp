//
//  StageCreater.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/09.
//
//

#include "Common.h"

USING_NS_CC;

std::mutex mtx;

bool StageCreater::init()
{
    if(!Layer::init())
        return false;
    this->scheduleUpdate();
    
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    _stage = Stage::create();
    _stage->stopAllActions();
    _stage->setScale(1.0f);
    this->addChild(_stage);
    
    SelectCrystals(true);
    createCrystals();
    SelectCrystals(false);
    
    return true;
}

void StageCreater::update(float delta)
{
    ///100個以下になったらステージを再生成する
    if(_stage->getChildrenCount() <= 100){
        _stage->removeFromParentAndCleanup(true);
        _stage = Stage::create();
        this->addChild(_stage);
        createCrystals();
        SelectCrystals(false);
    }
}

void StageCreater::createCrystals()
{
    auto stage = dynamic_cast<Stage*>(_stage);
    auto batch = stage->_crystalBatch;
    
    auto sprite = NormalCrystal::create(batch);
    
    Size size = sprite->getContentSize()*sprite->getScaleX();
    
    float* width = &size.width;
    float* height = &size.height;
    
    //60=壁の厚さ
    Vec2 basePos = Vec2(60+(*width)/2,60+(*height)/2+25);
    
    
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            Sprite* crystal;
            
            switch(_Selected[i][j])
            {
                case NORMAL:
                    crystal = NormalCrystal::create(batch);
                    break;
                case TIME:
                    crystal = TimeCrystal::create(batch);
                    break;
                case BALL:
                    crystal = BallCrystal::create(batch);
                    break;
                case EXPLOSION:
                    crystal = ExplosionCrystal::create(batch);
                    break;
                default:
                    continue;
                    break;
            }

            crystal->setPosition(basePos+Vec2(j*(*width),
                                              i*(*height)));
            
            _stage->addChild(crystal);
            
        }
    }
}

//ランダムにクリスタルの配置を選択する関数
//引数にはゲーム開始時最初の選択であったらtrue
void StageCreater::SelectCrystals(bool isFirstSelect)
{
    //一度全ての要素をノーマルクリスタルに
    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0 ; j < COL; j++)
        {
            _Selected[i][j] = NORMAL;
        }
    }
    
    int row[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
    int col[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
    
    for(int i = 0, lenR = 24, lenC = 15; i < 5; i++, lenR--,lenC--)
    {
        int r = random(0, lenR-1);
        int c = random(0, lenC-1);
        
        if(i <= 1)
            _Selected[row[r]][col[c]] = TIME;
        else if(i <= 3)
            _Selected[row[r]][col[c]] = BALL;
        else if(i == 4)
            _Selected[row[r]][col[c]] = EXPLOSION;
        
        row[r] = row[lenR-1];
        col[c] = col[lenC-1];
    }
    
    //ゲーム開始時の最初の選択の時の場合に
    //ボールと特殊クリスタルが重なることを防ぐために以下の処理をする
    if(isFirstSelect)
    {
        if(_Selected[12][6] != NORMAL ||
           _Selected[12][7] != NORMAL ||
           _Selected[13][6] != NORMAL ||
           _Selected[13][7] != NORMAL){
            SelectCrystals(true);
        }
        
        
        _Selected[12][6] = -1;
        _Selected[12][7] = -1;
        _Selected[13][6] = -1;
        _Selected[13][7] = -1;
    }
}
