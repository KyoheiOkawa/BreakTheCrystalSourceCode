//
//  MainScene.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include "Common.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto physicsWorld = scene->getPhysicsWorld();
    physicsWorld->setGravity(Vec2::ZERO);
    
    /*衝突判定の範囲を確認するときこのコメントを外す*/
    //physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MainScene::init()
{
    if(!LayerColor::initWithColor(Color4B::BLACK))
        return false;
    
    auto manager = PrototypeModeManager::getInstance();
    
    this->scheduleUpdate();
    
    LoadTextureCache();
    
    _state = GameState::START;
    _leftTime = LEFT_TIME;
    _destroyedCrystals = 0;
    
    _BallBatch = SpriteBatchNode::create(manager->_ballTexturePath.at(manager->_selectedBall));
    this->addChild(_BallBatch);
    
    AddNode();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    criadx2le::loadAcbFile("adx/ProtoType.acb","adx/ProtoType.awb");
    criadx2le::playCueById(PrototypeModeManager::getInstance()->_BgmId);
    criadx2le::playCueById(SE_BTC_VOICE);
    
    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void MainScene::onTouchMoved(Touch* touch, Event* event)
{
    
}

//ゲーム開始処理
void MainScene::onTouchEnded(Touch* touch, Event* event)
{
    if(_state == GameState::START){
        Vec2 dir = touch->getLocation() - touch->getStartLocation();
        
        float minLength = 50.0f;//フリックがこれ以上の距離になったらフリック判定
        
        Vec2 ballStartDir;//ゲーム開始時のボールの動き出す方向
        
        //フリックと判定されたらフリックした方向にボールを動かす
        if(dir.getLength() >= minLength){
            ballStartDir = dir.getNormalized();
        }
        //フリック判定がされていない（タッチ判定された）時はランダムな方向にボールを動かす
        else{
            float randomX = random(0, 360);
            float randomY = random(0, 360);
            ballStartDir = Vec2(cosf(MATH_DEG_TO_RAD(randomX)), sinf(MATH_DEG_TO_RAD(randomY)));
        }
        
        _state = GameState::PLAYING;
        auto ball = dynamic_cast<Ball*>(this->getChildByTag((int)Tag::BALL));
        ball->BallMove(ballStartDir);
    }
}

//メインゲームシーンで頻繁に使う画像のキャッシュを作成
void MainScene::LoadTextureCache()
{
    TextureCache* textureCache = Director::getInstance()->getTextureCache();
    auto manager = PrototypeModeManager::getInstance();
    
    textureCache->addImage(manager->_barTexturePath.at(manager->_selectedBar));
    textureCache->addImage("Texture/Crystal/Crystal2.png");
    textureCache->addImage(manager->_stageTexturePath.at(manager->_selectedBar));
    textureCache->addImage("particle/Break2.png");
}

void MainScene::AddNode()
{
    auto manager = PrototypeModeManager::getInstance();
    
    Size vs;
    Vec2 origin;
    
    manager->MultiResolution(origin, vs);
    
    //バックグラウンドのパーティクルを設定
    ParticleSystemQuad* particle = ParticleSystemQuad::create(manager->_particlePath.at(manager->_selectedBackGround));
    particle->setAutoRemoveOnFinish(true);
    particle->resetSystem();
    particle->setPosition(origin+vs/2);
    //使うバックグラウンドパーティクルの種類によって位置を変更する
    switch(manager->_selectedBackGround)
    {
        case 1:
            particle->setPositionY(origin.y);
            break;
        case 6:
            particle->setPosition(origin+Vec2(vs.width/2+100,750));
            break;
            
        default:
            break;
    }
    this->addChild(particle);
    
    _last3Count = Label::createWithTTF("3", USE_FONT_PATH, 500);
    _last3Count->setPosition(origin+vs/2);
    _last3Count->setVisible(false);
    _last3Count->setHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_last3Count);
    
    auto walls = Wall::create();
    this->addChild(walls);
    
    auto ball = Ball::create(_BallBatch);
    ball->setPosition(origin+vs/2+Vec2(0,-21));
    ball->setName("MainBall");
    this->addChild(ball,9);
    
    //メインボールの軌跡
    auto streak = MotionStreak::create(0.1f, 0, 50*ball->getScaleX(), Color3B::GRAY, "Texture/Other/line.png");
    streak->setName("BallStreak");
    streak->setFastMode(true);
    this->addChild(streak,0);
    
    auto barCreater = BarCreater::create();
    this->addChild(barCreater,8);
    
    auto stage = StageCreater::create();
    this->addChild(stage,2);
    
    auto UIlayer = MainUILayer::create();
    this->addChild(UIlayer,10);

}

void MainScene::update(float delta)
{
    criadx2le::update();
    
    //メインボールに奇跡をつける
    this->getChildByName("BallStreak")->setPosition(this->getChildByName("MainBall")->getPosition());
    
    switch (_state) {
        case GameState::START:
            StartFunc();
            break;
        case GameState::PLAYING:
            PlayingFunc(delta);
            break;
        case GameState::POSE:
            PoseFunc();
            break;
        case GameState::END:
            EndFunc();
            break;
            
            default:
            break;
    }
}

void MainScene::StartFunc()
{
    
}

void MainScene::PlayingFunc(float delta)
{
    _leftTime -= delta;
    
    //３秒前になったら３、２、１カウントを始める
    if(_leftTime <= 3){
        _last3Count->setVisible(true);
        
        int time = (int)floorf(_leftTime+1);
        _last3Count->setString(std::to_string(time));
    }
    else{
        _last3Count->setVisible(false);
    }
    
    if(_leftTime <= 0.0f){
        _leftTime = 0;
        _last3Count->setVisible(false);
        _state = GameState::END;
    }
}

void MainScene::PoseFunc()
{
    
}

void MainScene::EndFunc()
{
    auto manager = PrototypeModeManager::getInstance();
    manager->_Score = _destroyedCrystals;
    
    auto delay = DelayTime::create(1.5f);
    auto trans = CallFunc::create([this](){
        criadx2le::stopAll();
        criadx2le::releaseAcbFile();
        Scene* resultScene = ResultScene::createScene();
        auto trans = TransitionCrossFade::create(MAIN2RESULT_TIME, resultScene);
        Director::getInstance()->replaceScene(trans);
    });
    auto seq = Sequence::create(delay,trans, NULL);
    this->runAction(seq);

    this->unscheduleUpdate();
}

void MainScene::AddBrokenCrystalCount()
{
    if(_state == GameState::PLAYING)
        _destroyedCrystals++;
}
void MainScene::AddTime(float time)
{
    if(_state == GameState::PLAYING){
        _leftTime += time;
        if(_leftTime >= LEFT_TIME)
            _leftTime = LEFT_TIME;
    }
}

