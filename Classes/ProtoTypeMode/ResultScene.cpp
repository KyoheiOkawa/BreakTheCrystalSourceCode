//
//  ResultScene.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/10.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"
#include "CCSocialManager.h"
#include "NativeCodeLauncher.h"
#include "NendModule.h"
#include "NendInterstitialModule.h"

USING_NS_CC;

Scene* ResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool ResultScene::init()
{
    if(!LayerColor::initWithColor(Color4B::BLACK))
        return false;
    
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    auto Back = ui::Button::create("Texture/Result/Back.png");
    Back->setScale(3.0f);
    Back->setPosition(origin + vs/2);
    this->addChild(Back);
    
    ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/Result.plist");
    particle->setAutoRemoveOnFinish(true);
    particle->resetSystem();
    particle->setPosition(origin.x+vs.width/2,origin.y + vs.height);
    this->addChild(particle);
    
    //-----------------------------------------------
    //ハイスコア
    auto userDef = UserDefault::getInstance();
    unsigned long score = PrototypeModeManager::getInstance()->_Score;
    if(userDef->getIntegerForKey("HighScore") < score){
        userDef->setIntegerForKey("HighScore", (int)score);
        ///ゲームセンターにスコアを送信
        Cocos2dExt::NativeCodeLauncher::postHighScore(1, (int)score);
        
        ParticleSystemQuad* particle = ParticleSystemQuad::create("particle/Result2.plist");
        particle->setAutoRemoveOnFinish(true);
        particle->resetSystem();
        particle->setPosition(origin.x+vs.width/2,origin.y + vs.height);
        this->addChild(particle);
        
        auto highscoreChara = Label::createWithTTF("HIGHSCORE!!", "fonts/airstrike.ttf", 64);
        highscoreChara->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        highscoreChara->enableOutline(Color4B::BLACK,3);
        highscoreChara->setPosition(origin+Vec2(vs.width/2,vs.height/2 + 180 + 90));
        this->addChild(highscoreChara);
        
        auto blink = Blink::create(360, 360);
        highscoreChara -> runAction(blink);
    }
    //-----------------------------------------------
    
    auto scoreChara = Label::createWithTTF("SCORE", "fonts/airstrike.ttf", 100);
    scoreChara->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreChara->enableOutline(Color4B::BLACK,3);
    scoreChara->setPosition(origin+Vec2(vs.width/2,vs.height/2 + 90 + 90));
    this->addChild(scoreChara);
    
    
    auto scoreLabel = Label::createWithTTF("", "fonts/airstrike.ttf", 100);
    std::ostringstream ostr;
    ostr << ""  << score;
    scoreLabel->setString(ostr.str());
    scoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreLabel->enableOutline(Color4B::BLACK,3);
    scoreLabel->setPosition(origin+Vec2(vs.width/2,vs.height/2 + 90));
    this->addChild(scoreLabel);
    auto seAction = ScaleTo::create(0.5f, 1.2f);
    auto seAction2 = ScaleTo::create(0.5f, 1.0f);
    auto seSeq = Sequence::create(seAction, seAction2,NULL);
    auto seRepeat = RepeatForever::create(seSeq);
    scoreLabel->runAction(seRepeat);
    
    
    auto titleButton = ui::Button::create("Texture/Button/step2.png");
    titleButton->setScale(0.7f);
    titleButton->setPosition(origin + Vec2(vs.width/2,titleButton->getContentSize().height));
    this->addChild(titleButton);
    titleButton->addTouchEventListener(CC_CALLBACK_2(ResultScene::onTitleButton, this));
    
    
    auto retryButton = ui::Button::create("Texture/Button/loop2.png");
    retryButton->setScale(0.7f);
    retryButton->setPosition(origin + Vec2(vs.width/2,titleButton->getContentSize().height+retryButton->getContentSize().height +32));
    this->addChild(retryButton);
    retryButton->addTouchEventListener(CC_CALLBACK_2(ResultScene::onRetryButton, this));
    
    
    auto twitterButton = ui::Button::create("Texture/Result/twitter.png");
    twitterButton->setScale(1.0f);
    twitterButton->setPosition(origin + Vec2(vs.width-twitterButton->getContentSize().width*1.5f,twitterButton->getContentSize().height));
    this->addChild(twitterButton);
    twitterButton->addTouchEventListener(CC_CALLBACK_2(ResultScene::onTwitterButton, this));
    
    
    auto shareChara = Label::createWithTTF("TWITTER", "fonts/airstrike.ttf", 20);
    shareChara->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    shareChara->enableOutline(Color4B::BLACK,2);
    shareChara->setPosition(origin + Vec2(vs.width - twitterButton->getContentSize().width*1.5f,twitterButton->getContentSize().height*1.8f));
    this->addChild(shareChara);
    
    
    auto faceBookButton = ui::Button::create("Texture/Result/facebook.png");
    faceBookButton->setScale(1.0f);
    faceBookButton->setPosition(origin + Vec2(vs.width - twitterButton->getContentSize().width*1.5f,twitterButton->getContentSize().height + faceBookButton->getContentSize().height + 48));
    this->addChild(faceBookButton);
    faceBookButton->addTouchEventListener(CC_CALLBACK_2(ResultScene::onFaceBookButton, this));
    
    
    auto shareChara2 = Label::createWithTTF("facebook", "fonts/airstrike.ttf", 20);
    shareChara2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    shareChara2->enableOutline(Color4B::BLACK,2);
    shareChara2->setPosition(origin + Vec2(vs.width-twitterButton->getContentSize().width*1.5f,faceBookButton->getContentSize().height+twitterButton->getContentSize().height*1.8f + 48));
    this->addChild(shareChara2);
    

    auto retryChara = Label::createWithTTF("RESTART", "fonts/airstrike.ttf", 32);
    retryChara->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    retryChara->enableOutline(Color4B::BLACK,3);
    retryChara->setPosition(origin + Vec2(vs.width/2,titleButton->getContentSize().height+retryButton->getContentSize().height*1.5f+32));
    this->addChild(retryChara);
    
    auto titleChara = Label::createWithTTF("TITLE", "fonts/airstrike.ttf", 32);
    titleChara->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    titleChara->enableOutline(Color4B::BLACK,3);
    titleChara->setPosition(origin + Vec2(vs.width/2,titleButton->getContentSize().height*1.5f));
    this->addChild(titleChara);
    
    //-----------------------------------------------
    //ゲーム内マニーの実装By Kyohei
    int money = userDef->getIntegerForKey("Money");
    money += score / 1000;
    userDef->setIntegerForKey("Money", money);
    //-----------------------------------------------
    
    auto getmoneyLabel = Label::createWithTTF("", "fonts/airstrike.ttf", 48);
    std::ostringstream ostr3;
    ostr3 << "+ " << score/1000 << " BP";
    getmoneyLabel->setString(ostr3.str());
    getmoneyLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    getmoneyLabel->enableOutline(Color4B::BLACK,3);
    getmoneyLabel->setPosition(origin+Vec2(vs.width/2,vs.height/2));
    this->addChild(getmoneyLabel);
    
    auto moneyLabel = Label::createWithTTF("", "fonts/airstrike.ttf", 48);
    std::ostringstream ostr2;
    ostr2 << "TOTAL " << money <<" BP";
    moneyLabel->setString(ostr2.str());
    moneyLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    moneyLabel->enableOutline(Color4B::BLACK,3);
    moneyLabel->setPosition(origin+Vec2(vs.width/2,vs.height/2 -60));
    this->addChild(moneyLabel);
    
    //-----------------------------------------------
    //リザルト曲を再生
    criadx2le::loadAcbFile("adx/ProtoType.acb", "adx/ProtoType.awb");
    criadx2le::playCueById(MS_BTC_RESULT);
    //-----------------------------------------------
    
    //-----------------------------------------------
    //インタースティンシャル広告読み込み
    char interstitialApiKey[] = "MyAPIKey";
    char interstitialSpotID[] = "MySpotID";
    NendInterstitialModule::createNADInterstitial(interstitialApiKey, interstitialSpotID);
    //-----------------------------------------------
    
    return true;
}



void ResultScene::onTitleButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            
            auto delay = DelayTime::create(0.2f);
            auto func = CallFunc::create([](){
                Scene* titleScene = TitleScene::createScene();
                auto trans = TransitionCrossFade::create(1.0f, titleScene);
                Director::getInstance()->replaceScene(trans);
                
                NendInterstitialModule::showNADInterstitialView();
                
            });
            
            auto seq = Sequence::create(delay,func, NULL);
            this->runAction(seq);

            break;
        }
        default:
            break;
    }
}

void ResultScene::onRetryButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            
            auto delay = DelayTime::create(0.2f);
            auto func = CallFunc::create([](){
                Scene* mainScene = MainScene::createScene();
                auto trans = TransitionCrossFade::create(1.0f, mainScene);
                Director::getInstance()->replaceScene(trans);
                
                NendInterstitialModule::showNADInterstitialView();
            });
            
            auto seq = Sequence::create(delay,func, NULL);
            this->runAction(seq);
            break;
        }
        default:
            break;
    }
}

void ResultScene::onTwitterButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            
            if (CCSocialShare::SocialManager::isAvailable(CCSocialShare::Service::TWITTER)) {
                Size size = Director::getInstance()->getWinSize();
                RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
                texture->setPosition(Point(size.width / 2, size.height / 2));
                texture->begin();
                Director::getInstance()->getRunningScene()->visit();
                texture->end();
                
                std::function<void(RenderTexture* rt, const std::string& path)> hoge =
                [&](RenderTexture* rt, const std::string& path)
                {
                    std::function<void(CCSocialShare::PostResult result)> foo =
                    [](CCSocialShare::PostResult result)
                    {
                        if (result == CCSocialShare::PostResult::SUCCEED) {
                            // When to post is succeed
                            log("Done");
                        } else if (result == CCSocialShare::PostResult::CANCELED) {
                            // When to post is canceled
                            log("Canceled");
                        }
                    };
                    
                    CCSocialShare::SocialManager::postMessage(CCSocialShare::Service::TWITTER,"HIGH SCORE!!",path.c_str(),foo);
                };
            
                texture->saveToFile("screenshot.png",Image::Format::PNG,true,hoge);
            }
            else{
                log("設定されてない");
                MessageBox("Twitterアカウントが設定されていません","Twitter account not found.");
            }
            break;
        }
        default:
            break;
    }
}

void ResultScene::onFaceBookButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            if (CCSocialShare::SocialManager::isAvailable(CCSocialShare::Service::FACEBOOK)) {
                Size size = Director::getInstance()->getWinSize();
                RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
                texture->setPosition(Point(size.width / 2, size.height / 2));
                texture->begin();
                Director::getInstance()->getRunningScene()->visit();
                texture->end();
                
                std::function<void(RenderTexture* rt, const std::string& path)> hoge
                = [&](RenderTexture* rt, const std::string& path)
                {
                    std::function<void(CCSocialShare::PostResult result)> foo =
                    [](CCSocialShare::PostResult result)
                    {
                        if (result == CCSocialShare::PostResult::SUCCEED) {
                            // When to post is succeed
                            log("Done");
                        } else if (result == CCSocialShare::PostResult::CANCELED) {
                            // When to post is canceled
                            log("Canceled");
                        }
                    };
                    
                    CCSocialShare::SocialManager::postMessage(CCSocialShare::Service::FACEBOOK,"HIGH SCORE!!",path.c_str(),foo);
                };
                
                texture->saveToFile("screenshot.png",Image::Format::PNG,true,hoge);
            }
            else{
                log("設定されてない");
                MessageBox("Facebookアカウントが設定されていません","Facebook account not found.");
            }
            break;
        }
        default:
            break;
    }
}
