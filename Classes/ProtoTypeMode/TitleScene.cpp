//
//  TitleScene.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"
#include "NativeCodeLauncher.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = TitleScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool TitleScene::init()
{
    if(!LayerColor::initWithColor(Color4B::BLACK))
        return false;
    
    criadx2le::loadAcbFile("adx/ProtoType.acb","adx/ProtoType.awb");
    AddNode();
    
    return true;
}

void TitleScene::AddNode()
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    auto titleLogo = Sprite::create("Texture/UI/Text/titlelogo2.png");
    titleLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    titleLogo->setPosition(origin+Vec2(vs.width/2,vs.height-100));
    auto taction = TintTo::create(1.0f, 150, 150, 150);
    auto taction2 = TintTo::create(1.0f, 255, 255, 255);
    auto tseq = Sequence::create(taction,taction2, NULL);
    auto trep = RepeatForever::create(tseq);
    titleLogo->runAction(trep);
    this->addChild(titleLogo);
    
    _backGround = TitleStage::create();
    this->addChild(_backGround);
    
    unsigned int score = UserDefault::getInstance()->getIntegerForKey("HighScore");
    auto scoreLabel = Label::createWithTTF("", USE_FONT_PATH, 64);
    
    //ハイスコアをゲームセンターへ送信
    Cocos2dExt::NativeCodeLauncher::postHighScore(1, (int)score);
    
    std::ostringstream ostr;
    ostr << "HighScore : " << std::setw(5) << std::setfill(' ') << std::right << score;
    scoreLabel->setString(ostr.str());
    
    scoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreLabel->setPosition(origin+Vec2(vs.width/2,vs.height-titleLogo->getContentSize().height-140));
    
    scoreLabel->enableShadow(Color4B::RED);
    this->addChild(scoreLabel);
    
    auto flickDir = Sprite::create("Texture/Other/flickChange.png");
    flickDir->setPosition(origin+Vec2(vs.width/2,vs.height/3));
    flickDir->setScale(vs.width/flickDir->getContentSize().width);
    this->addChild(flickDir);
    auto faction1 = TintTo::create(0.5f, Color3B(150,150,150));
    auto faction2 = TintTo::create(0.5f, Color3B::WHITE);
    auto fseq = Sequence::create(faction1,faction2, NULL);
    auto frepeat = RepeatForever::create(fseq);
    flickDir->runAction(frepeat);
    
    _playButton = ui::Button::create("Texture/Button/play.png");
    _playButton->setScale(2.0f);
    _playButton->setPosition(origin + Vec2(vs.width/2+18,_playButton->getContentSize().height));
    this->addChild(_playButton);
    _playButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onPlayButton, this));
    
    _playLabel = ui::Button::create("Texture/Button/PlayRich.png");
    _playLabel->setScale(0.4f);
    _playLabel->setPosition(origin + Vec2(vs.width/2,_playButton->getContentSize().height*2.0f));
    this->addChild(_playLabel);
    
    auto rankingButton = ui::Button::create("Texture/Button/ranking.png");
    rankingButton->setScale(0.4f);
    rankingButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    rankingButton->setPosition(origin+Vec2(vs.width-32,20));
    this->addChild(rankingButton);
    rankingButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onRankingButton, this));
    
    auto shoppingButton = ui::Button::create("Texture/Button/basket.png");
    shoppingButton->setScale(0.4f);
    shoppingButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    shoppingButton->setPosition(origin+Vec2(vs.width-36,rankingButton->getContentSize().height*rankingButton->getScaleX()+50));
    this->addChild(shoppingButton);
    shoppingButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onShoppingButton, this));
    
    auto tutorialButton = ui::Button::create("Texture/Button/HowToPlay.png");
    tutorialButton->setScale(0.5f);
    tutorialButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    tutorialButton->setPosition(origin+Vec2(20,20));
    this->addChild(tutorialButton);
    tutorialButton->addTouchEventListener(CC_CALLBACK_2(TitleScene::onTutorialButton, this));
    
    auto shopChara = Label::createWithTTF("BP SHOP", "fonts/airstrike.ttf", 28);
    shopChara->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    shopChara->enableOutline(Color4B::BLACK,2);
    shopChara->setPosition(origin+Vec2(vs.width-28,rankingButton->getContentSize().height*rankingButton->getScaleX()*2.0f+50));
    this->addChild(shopChara);
    
    auto rankChara = Label::createWithTTF("RANKING", "fonts/airstrike.ttf", 28);
    rankChara->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    rankChara->enableOutline(Color4B::BLACK,2);
    rankChara->setPosition(origin+Vec2(vs.width-20,rankingButton->getContentSize().height*rankingButton->getScaleX()+15));
    this->addChild(rankChara);
    
    NendModule::release("MySpotId");
    char apikey[] = "MyApiKey";
    char spotID[] = "MySpotId";
    NendModule::createNADViewTop(apikey, spotID,true);
    
}

void TitleScene::onPlayButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {

            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            
            auto manager = PrototypeModeManager::getInstance();
            auto selectedNum = dynamic_cast<TitleStage*>(_backGround)->_selectedNum;
            manager->_selectedBackGround = selectedNum;
            manager->_BgmId = manager->_BgmFirstId + selectedNum;
            
            auto delay = DelayTime::create(0.2f);
            auto func = CallFunc::create([](){
                criadx2le::stopAll();
                criadx2le::releaseAcbFile();
                Scene* mainScene = MainScene::createScene();
                auto trans = TransitionCrossFade::create(1.0f, mainScene);
                Director::getInstance()->replaceScene(trans);
            });
            auto seq = Sequence::create(delay,func, NULL);
            this->runAction(seq);
            
            break;
        }
        default:
            break;
    }
}

void TitleScene::onShoppingButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch(type){
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            auto shop = TitleShop::create();
            this->addChild(shop);
            break;
        }
            default:
            break;
    }
}

void TitleScene::onRankingButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            Cocos2dExt::NativeCodeLauncher::openRanking();
            break;
            
        default:
            break;
    }
}

void TitleScene::onTutorialButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::subPlayCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::subPlayCueById(SE_BUTTON_OFF);
            auto tutorial = TutorialLayer::create();
            tutorial->setPosition(Director::getInstance()->getVisibleOrigin());
            this->addChild(tutorial);
            break;
        }
        default:
            break;
    }
}
