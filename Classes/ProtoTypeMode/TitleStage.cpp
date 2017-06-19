//
//  TitleStage.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/22.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"

USING_NS_CC;

bool TitleStage::init()
{
    if(!Layer::init())
        return false;
    
    criadx2le::playCueById(PrototypeModeManager::getInstance()->_BgmFirstId);
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    //ステージで使う背景用パーティクルをまとめて持つノード
    _particleNode = Node::create();
    _particleNode->setPosition(origin);
    this->addChild(_particleNode);
    
    auto manager = PrototypeModeManager::getInstance();
    auto particlePath = manager->_particlePath;
    
    //ステージで使うパーティクルを全部追加する
    for(int i = 0; i < 7; i++){
        _backParticle.pushBack(ParticleSystemQuad::create(particlePath.at(i)));
    }
    
    std::vector<std::string> musicInfo{
        "BreakTheCrystal\nComposer:KyoheiOkawa",
        "Start\nComposer:KyoheiOkawa",
        "Breaker\nComposer:kingbee",
        "Elica\nComposer:KyoheiOkawa",
        "Reflections\nComposer:kingbee",
        "Untitled\nComposer:KyoheiOkawa",
        "Emotion\nComposer:KyoheiOkawa"
    };
    
    //_particleNodeにパーティクルをそれぞれまとめて追加する
    int i = 0;
    _selectedNum = 0;
    for(auto back : _backParticle){
        back->stop();
        
        back->setPosition(origin+vs/2+Vec2(vs.width*i,0));
        //パーティクルの種類によって位置を変更
        switch(i)
        {
            case 1:
                back->setPositionY(origin.y);
                break;
            case 6:
                back->setPosition(origin+Vec2(vs.width*i+vs.width/2+100,750));
                break;
                
                default:
                break;
        }

        _particleNode->addChild(back);
        
        //ミュージックの曲名と作曲者のラベルを設定
        auto musicLabel = Label::createWithTTF(musicInfo.at(i), USE_FONT_PATH, 40);
        musicLabel->setHorizontalAlignment(TextHAlignment::CENTER);
        musicLabel->setPosition(origin+vs/2+Vec2(vs.width*i,0));
        _particleNode->addChild(musicLabel);
        
        //ステージがロックされていたら選択できなくする
        if(JudgeIsLocked(i)){
      
            auto lockSprite = Sprite::create("Texture/Button/locked.png");
            lockSprite->setPosition(origin+vs/2+Vec2(vs.width*i,0));
            _particleNode->addChild(lockSprite);
            
            std::ostringstream ostr;
            ostr << "Get highscore\n" << STAGE_UNLOCK_SCORE[i] << "\npoints";
            
            auto comment = Label::createWithTTF(ostr.str(),USE_FONT_PATH,50);
            comment->setColor(Color3B::RED);
            comment->setHorizontalAlignment(TextHAlignment::CENTER);
            comment->setPosition(origin+vs/2+Vec2(vs.width*i,-lockSprite->getContentSize().height/2.0f-comment->getContentSize().height/2.0f));
            _particleNode->addChild(comment);
            
        }
        
        i++;
    }
    
    changeSelect();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(TitleStage::onTouchBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TitleStage::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TitleStage::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool TitleStage::onTouchBegin(Touch* touch, Event* event)
{
    _parNodeBeforePos = _particleNode->getPosition();
    
    return true;
}

//ここではタップしている間にページを途中までめくっているような処理をしている
void TitleStage::onTouchMoved(Touch* touch, Event* event)
{
    float length = touch->getLocation().x - touch->getStartLocation().x;
    _particleNode->setPosition(_parNodeBeforePos+Vec2(length,0));
}

//指を離したときにページをめくる、または戻す処理をする
void TitleStage::onTouchEnded(Touch* touch, Event* event)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    auto _bgmFirstId = PrototypeModeManager::getInstance()->_BgmFirstId;
    
    float actionSpeed = 0.25f;
    
    float length = touch->getLocation().x - touch->getStartLocation().x;
    
    //右にフリックした場合
    if(length > 0){
        //フリックした長さが画面の横幅の４分の１以上であればページをめくる
        if(length >= vs.width/4){
            //いま選ばれているページが一番左ではなかったらめくる
            if(_selectedNum > 0){
                criadx2le::stopAll();
                _selectedNum--;
                if(!JudgeIsLocked(_selectedNum)){
                    criadx2le::playCueById(_bgmFirstId+_selectedNum);
                }
                
                auto move = MoveTo::create(actionSpeed, Vec2(vs.width*-_selectedNum,0));
                auto func = CallFunc::create([this](){
                    this->changeSelect();
                });
                auto seq = Sequence::create(move,func, NULL);
                _particleNode->runAction(seq);
            }
            //選ばれているページが一番左であったらページの座標を戻す
            else{
                auto move = MoveTo::create(actionSpeed, Vec2(0,0));
                _particleNode->runAction(move);
            }
        }
        //フリックした長さが画面の横幅の４分の１以下であった場合いま選ばれているページの座標を指定のいちに戻す
        else{
            auto move = MoveTo::create(actionSpeed, Vec2(vs.width*-_selectedNum,0));
            _particleNode->runAction(move);
        }
    }
    //左にフリックした場合
    else if(length < 0){
        //以下の処理は右にフリックした場合の時とほとんど同じ
        if(length*-1 >= vs.width/4){
            if(_selectedNum < _backParticle.size() - 1){
                criadx2le::stopAll();
                _selectedNum++;
                if(!JudgeIsLocked(_selectedNum)){
                    criadx2le::playCueById(_bgmFirstId+_selectedNum);
                }
                
                auto move = MoveTo::create(actionSpeed, Vec2(vs.width*-_selectedNum,0));
                auto func = CallFunc::create([this](){
                    this->changeSelect();
                });
                auto seq = Sequence::create(move,func, NULL);
                _particleNode->runAction(seq);
            }
            else{
                auto move = MoveTo::create(actionSpeed, Vec2(vs.width*-(_backParticle.size()-1),0));
                _particleNode->runAction(move);
            }
        }
        else{
            auto move = MoveTo::create(actionSpeed, Vec2(vs.width*-_selectedNum,0));
            _particleNode->runAction(move);
        }
    }
}

//選ばれているステージの前後のパーティクルは再生しておく関数
void TitleStage::changeSelect()
{
    _backParticle.at(_selectedNum)->start();
    
    
    auto parent = this->getParent();
    auto titleScene = dynamic_cast<TitleScene*>(parent);
    
    if(titleScene != NULL){
        auto playBt = titleScene->GetPlayButton();
        auto playLb = titleScene->GetPlayLabel();
        
        if(JudgeIsLocked(_selectedNum)){
            playBt->setColor(Color3B(100,100,100));
            playLb->setColor(Color3B(100,100,100));
            playBt->setTouchEnabled(false);
        }
        else{
            playBt->setColor(Color3B::WHITE);
            playLb->setColor(Color3B::WHITE);
            playBt->setTouchEnabled(true);
        }
    }
    
    if(_selectedNum != 0)
        _backParticle.at(_selectedNum-1)->start();
    if(_selectedNum != _backParticle.size()-1)
        _backParticle.at(_selectedNum+1)->start();
}

//ロックされていたらtrueを返す
//引数にはステージのインデックス
bool TitleStage::JudgeIsLocked(int i)
{
    if(IS_LOCKEDMODE){
        int highScore = UserDefault::getInstance()->getIntegerForKey("HighScore");
        
        if(highScore < STAGE_UNLOCK_SCORE[i]){
            return true;
        }
        
    }
    
    return false;
}
