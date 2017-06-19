//
//  MainUILayer.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/07.
//
//

#include <sstream>
#include <iomanip>
#include "Common.h"

USING_NS_CC;

bool MainUILayer::init()
{
    if(!Layer::init())
        return false;
    
    this->scheduleUpdate();
    
    Hierarchy();
    
    return true;
}

void MainUILayer::Hierarchy()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    auto UIbar1 = Sprite::create("Texture/UI/UIback6.png");
    UIbar1->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    UIbar1->setPosition(origin);
    UIbar1->setScaleX(vs.width/UIbar1->getContentSize().width);
    this->addChild(UIbar1);
    
    //時間表示ラベル
    _time = Label::createWithTTF("TIME: 30.00", USE_FONT_PATH, 45);
    _time->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _time->setPosition(origin+Vec2(16,vs.height-100-16));
    _time->setColor(Color3B(0, 0, 0));
    _time->enableShadow(Color4B(0, 0, 0,128));
    this->addChild(_time);
    
    //壊したクリスタルの数ラベル
    _broken = Label::createWithTTF("Crys: 00000", USE_FONT_PATH, 45);
    _broken->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _broken->setPosition(origin+Vec2(vs.width-_broken->getContentSize().width-20-16,vs.height-100-16));
    _broken->setColor(Color3B(0, 0, 0));
    _broken->enableShadow(Color4B(0, 0, 0,128));
    this->addChild(_broken);
    
    //最初と最後に表示するスプライト
    _StartEnd = Label::createWithTTF("FLICK TO START", USE_FONT_PATH, 64);
    _StartEnd->enableOutline(Color4B::BLACK,6);
    _StartEnd->setPosition(origin+Vec2(vs.width/2,vs.height/2-90));
    this->addChild(_StartEnd);
    
    //ポーズボタン
    _pauseBt = ui::Button::create("Texture/Button/pause.png");
    _pauseBt->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    _pauseBt->setPosition(origin+Vec2(vs.width,0));
    _pauseBt->setScale(0.5f);
    
    this->addChild(_pauseBt);
    _pauseBt->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onPauseButton,this));
    
    //pausePane
    _pausePanel = LayerColor::create(Color4B(0,0,0,150));
    this->addChild(_pausePanel);
    _pausePanel->setVisible(false);
    
    //再開ボタン
    _panelResume = ui::Button::create("Texture/Button/play.png");
    _panelResume->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onResumeButton, this));
    _panelResume->setTouchEnabled(false);
    _panelResume->setScale(2.0f);
    _panelResume->setPosition(origin+Vec2(vs.width/2,vs.height*3/4.0f));
    _pausePanel->addChild(_panelResume);
    
    //リトライボタン
    _panelRetry = ui::Button::create("Texture/Button/loop.png");
    _panelRetry->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onRetryButton, this));
    _panelRetry->setTouchEnabled(false);
    _panelRetry->setScale(2.0f);
    _panelRetry->setPosition(origin+Vec2(vs.width/2,vs.height*2/4.0f));
    _pausePanel->addChild(_panelRetry);
    
    //タイトルへ戻るボタン
    _panelReturn = ui::Button::create("Texture/Button/step.png");
    _panelReturn->addTouchEventListener(CC_CALLBACK_2(MainUILayer::onReturnButton, this));
    _panelReturn->setTouchEnabled(false);
    _panelReturn->setScale(2.0f);
    _panelReturn->setPosition(origin+Vec2(vs.width/2,vs.height*1/4.0f));
    _pausePanel->addChild(_panelReturn);
    
    //FlickToStartのアニメーション
    auto seAction = ScaleTo::create(0.5f, 1.15f);
    auto seAction2 = ScaleTo::create(0.5f, 1.0f);
    auto seSeq = Sequence::create(seAction, seAction2,NULL);
    auto seRepeat = RepeatForever::create(seSeq);
    _StartEnd->runAction(seRepeat);
}

void MainUILayer::update(float delta)
{
    auto parent = dynamic_cast<MainScene*>(this->getParent());
    if(!parent)
        log("MainUILayerはMainSceneの子に設定してください");
    
    float time = parent->GetTime();
    unsigned long broken = parent->GetBrokenCrystalsCount();
    
    std::ostringstream ostr;
    ostr << "TIME: " << std::fixed << std::setprecision(2) << time;
    _time->setString(ostr.str());
    
    ostr.str("");
    ostr << "CRYS: " << std::setw(5) << std::setfill('0') << std::right << broken;
    _broken->setString(ostr.str());
    
    //stateがPLAYING,END以外の時は_StartEndは非表示にする
    if(parent->GetState() == (GameState::PLAYING || GameState::POSE)){
        _StartEnd->setOpacity(0);
        _StartEnd->stopAllActions();
    }
    
    //タイムアップカウントの表示
    if(parent->GetState() == GameState::END){
        auto origin = Director::getInstance()->getVisibleOrigin();
        auto vs = Director::getInstance()->getVisibleSize();
        _StartEnd->setOpacity(255);
        _StartEnd->setScale(1.5f);
        _StartEnd->setString("TIME UP");
        _StartEnd->setPosition(origin+vs/2);
        
        auto scale = ScaleTo::create(MAIN2RESULT_TIME, 2.0f);
        auto fadeout = FadeOut::create(MAIN2RESULT_TIME);
        auto spawn   = Spawn::create(scale,fadeout, NULL);
        _StartEnd->runAction(spawn);
        
        this->unscheduleUpdate();
    }
}

//ポーズボタン押された時の処理
void MainUILayer::onPauseButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            auto parent = this->getParent();
            
            parent->pause();
            for(auto child : parent->getChildren()){
                if(child->getTag() == (int)Tag::BALL){
                    child->getPhysicsBody()->setEnabled(false);
                    child->pause();
                }
                else if(child->getName() == "BarCreater")
                    child->pause();
            }
            criadx2le::pause();
            
            //ポーズボタン押せなくする
            _pauseBt->setBright(false);
            _pauseBt->setTouchEnabled(false);
            
            //ポーズパネル表示
            _pausePanel->setVisible(true);
            _panelResume->setTouchEnabled(true);
            _panelRetry->setTouchEnabled(true);
            _panelReturn->setTouchEnabled(true);
            
            break;
        }
        default:
            break;
    }
}

//再開ボタン押された時の処理
void MainUILayer::onResumeButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            auto parent = this->getParent();
            
            parent->resume();
            for(auto child : parent->getChildren()){
                if(child->getTag() == (int)Tag::BALL){
                    child->getPhysicsBody()->setEnabled(true);
                    child->resume();
                }
                else if(child->getName() == "BarCreater")
                    child->resume();
            }
            
            criadx2le::resume();
            
            //ポーズボタン押せるようにする
            _pauseBt->setBright(true);
            _pauseBt->setTouchEnabled(true);
            
            //ポーズパネル非表示
            _pausePanel->setVisible(false);
            _panelResume->setTouchEnabled(false);
            _panelRetry->setTouchEnabled(false);
            _panelReturn->setTouchEnabled(false);
            break;
        }
            
        default:
            break;
    }
}

//リトライボタン押された時の処理
void MainUILayer::onRetryButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            
            auto delay = DelayTime::create(0.2f);
            auto func = CallFunc::create([](){
                criadx2le::stopAll();
                criadx2le::releaseAcbFile();
                criadx2le::resume();
                Scene* mainScene = MainScene::createScene();
                auto trans = TransitionCrossFade::create(1.0f, mainScene);
                Director::getInstance()->replaceScene(trans);
            });
            auto seq = Sequence::create(delay,func, NULL);
            this->runAction(seq);
        }
            break;
            
        default:
            break;
    }
}

//タイトルへ戻るボタン押された時の処理
void MainUILayer::onReturnButton(Ref *pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            
            auto delay = DelayTime::create(0.2f);
            auto func = CallFunc::create([](){
                criadx2le::stopAll();
                criadx2le::releaseAcbFile();
                criadx2le::resume();
                Scene* titleScene = TitleScene::createScene();
                auto trans = TransitionCrossFade::create(1.0f, titleScene);
                Director::getInstance()->replaceScene(trans);
            });
            auto seq = Sequence::create(delay,func, NULL);
            this->runAction(seq);
        }
            break;
            
        default:
            break;
    }
}
