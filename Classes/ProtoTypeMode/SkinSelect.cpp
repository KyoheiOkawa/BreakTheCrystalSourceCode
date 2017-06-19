//
//  SkinSelect.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/24.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"

USING_NS_CC;

bool SkinSelect::init()
{
    if(!cocos2d::ui::ScrollView::init())
        return false;
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    auto manager = PrototypeModeManager::getInstance();
    
    this->setDirection(ui::ScrollView::Direction::VERTICAL);
    this->setBounceEnabled(true);
    
    auto skinSelectLayer = LayerColor::create(Color4B(25, 54, 102,150), vs.width, vs.height*3.5f);
    skinSelectLayer->setPosition(Vec2::ZERO);
    
    auto skinSelect = Label::createWithTTF("Ball Select", USE_FONT_PATH, 60);
    skinSelect->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    skinSelect->setPosition(Vec2(vs.width/2,skinSelectLayer->getContentSize().height));
    skinSelectLayer->addChild(skinSelect);
    
    //------------------------------------------------------------------------
    //ボール
    Vector<Sprite*> balls{
        Sprite::create("Texture/Ball/HQ/Ball.png"),
        Sprite::create("Texture/Ball/HQ/Ball2.png"),
        Sprite::create("Texture/Ball/HQ/Ball3.png"),
        Sprite::create("Texture/Ball/HQ/Ball4.png"),
        Sprite::create("Texture/Ball/HQ/Ball5.png"),
        Sprite::create("Texture/Ball/HQ/Ball6.png"),
        Sprite::create("Texture/Ball/HQ/Ball7.png"),
        Sprite::create("Texture/Ball/HQ/Ball8.png"),
        Sprite::create("Texture/Ball/HQ/Ball9.png"),
        Sprite::create("Texture/Ball/HQ/Ball10.png")
    };
    
    _radioButtonGroupBall = ui::RadioButtonGroup::create();
    skinSelectLayer->addChild(_radioButtonGroupBall);
    
    for(int i = 0; i < balls.size(); i++)
    {
        auto radioButton = ui::RadioButton::create("Texture/Button/radioButtonOff.png","Texture/Button/radioButtonOn.png");
        
        auto offSet = 100;
        auto size = 0.8f;
        balls.at(i)->setScale(size);
        auto pos = Vec2(skinSelectLayer->getContentSize().width*((i%2==0)? 1: 3)/4.0f,skinSelectLayer->getContentSize().height-
                        (balls.at(i)->getContentSize().height*balls.at(i)->getScaleX()*((i/2)+1))-(i/2)*offSet);
        
        balls.at(i)->setPosition(pos);
        balls.at(i)->setTag(i);
        
        radioButton->setScale(size);
        radioButton->setPosition(pos);
        radioButton->setTag(i);
        radioButton->addTouchEventListener(CC_CALLBACK_2(SkinSelect::onChangedRadioButtonSelectBall, this));
        _radioButtonGroupBall->addRadioButton(radioButton);
        
        skinSelectLayer->addChild(balls.at(i));
        skinSelectLayer->addChild(radioButton);
        
        if(!isUnlockedBall(i)){
            auto locked = Sprite::create("Texture/Button/locked.png");
            locked->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            locked->setPosition(Vec2::ZERO);
            locked->setOpacity(150);
            
            std::ostringstream ostr;
            ostr << BALL_FEE[i] << "BP";
            auto value = Label::createWithTTF(ostr.str(), USE_FONT_PATH, 60);
            value->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
            value->setPosition(Vec2(radioButton->getContentSize().width/2,0));
            
            radioButton->addChild(locked);
            radioButton->addChild(value);
        }
    }
    
    _radioButtonGroupBall->setSelectedButton(manager->_selectedBall);
    //------------------------------------------------------------------------
    
    //------------------------------------------------------------------------
    //バー
    Vector<Sprite*> bars;
    for(int i = 0; i < 16; i++){
        bars.pushBack(Sprite::create(manager->_barTexturePath[i]));
    }
    
    auto barSelect = Label::createWithTTF("Bar & Wall Select", USE_FONT_PATH, 60);
    barSelect->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    barSelect->setPosition(Vec2(vs.width/2,balls.at(balls.size()-1)->getPositionY()-200));
    skinSelectLayer->addChild(barSelect);
    
    _radioButtonGroupBar = ui::RadioButtonGroup::create();
    skinSelectLayer->addChild(_radioButtonGroupBar);
    
    for(int i = 0; i < bars.size(); i++)
    {
        auto radioButton = ui::RadioButton::create("Texture/Button/radioButtonOff.png","Texture/Button/radioButtonOn.png");
        
        auto offSet = 100;
        auto size = 0.8f;
        bars.at(i)->setScale(0.5f*size-0.05f);
        
        auto pos = Vec2(skinSelectLayer->getContentSize().width*((i%2==0)?1:3)/4.0f,
                        barSelect->getPositionY()
                        -((bars.at(i)->getContentSize().height*bars.at(i)->getScaleX())*((i/2)+1))-(i/2)*offSet);
        
        bars.at(i)->setPosition(pos);
        bars.at(i)->setTag(i);
        
        radioButton->setScale(size);
        radioButton->setPosition(pos);
        radioButton->setTag(i);
        radioButton->addTouchEventListener(CC_CALLBACK_2(SkinSelect::onChangedRadioButtonSelectBar, this));
        _radioButtonGroupBar->addRadioButton(radioButton);
        
        skinSelectLayer->addChild(bars.at(i));
        skinSelectLayer->addChild(radioButton);
        
        if(!isUnlockedBar(i)){
            auto locked = Sprite::create("Texture/Button/locked.png");
            locked->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            locked->setPosition(Vec2::ZERO);
            locked->setOpacity(150);
            
            std::ostringstream ostr;
            ostr << BAR_FEE[i] << "BP";
            auto value = Label::createWithTTF(ostr.str(), USE_FONT_PATH, 60);
            value->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
            value->setPosition(Vec2(radioButton->getContentSize().width/2,0));
            
            radioButton->addChild(locked);
            radioButton->addChild(value);
        }
    }
    
    _radioButtonGroupBar->setSelectedButton(manager->_selectedBar);
    //------------------------------------------------------------------------
    
    this->addChild(skinSelectLayer);
    
    this->setInnerContainerSize(skinSelectLayer->getContentSize());
    
    this->setContentSize(Size(skinSelectLayer->getContentSize().width,vs.height*3.0f/4.0f));
    
    setRadioButtonTouchEnableBall();
    setRadioButtonTouchEnableBar();
    
    return true;
}

void SkinSelect::onChangedRadioButtonSelectBall(Ref* pSender,cocos2d::ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            
            auto bt = dynamic_cast<ui::RadioButton*>(pSender);
            if(bt != NULL){
                auto manager = PrototypeModeManager::getInstance();
                auto userDef = UserDefault::getInstance();
                
                //もしアンロックされていない場合は
                if(!isUnlockedBall(bt->getTag())){
                    auto confirm = ConfirmationLayer::create([this,userDef,manager,bt](){
                        //南京錠と値段ラベルの表示を消す
                        bt->removeAllChildrenWithCleanup(true);
                        
                        //残りBPをボールの値段分ひく
                        auto money = userDef->getIntegerForKey("Money");
                        money -= BALL_FEE[bt->getTag()];
                        userDef->setIntegerForKey("Money", money);
                        
                        //残りBPが少なくなったことで買えなくなったボールのボタンを押せなくする
                        setRadioButtonTouchEnableBall();
                        
                        //残りBPの表示ラベルを更新する
                        auto parent = this->getParent();
                        auto shop = dynamic_cast<TitleShop*>(parent);
                        if(shop != NULL){
                            shop->setMoneyLabel();
                        }
                        
                        //ボールをアンロック済みとする
                        std::ostringstream ostr;
                        ostr << "ball" << bt->getTag();
                        userDef->setBoolForKey(ostr.str().c_str(), true);
                        
                        //マネージャーに使うボールのインデックスを教える
                        manager->_selectedBall = bt->getTag();
                        userDef->setIntegerForKey("selectedBall", bt->getTag());
                        
                        _radioButtonGroupBall->setSelectedButton(bt->getTag());
                    });
                    auto vs = Director::getInstance()->getVisibleSize();
                    confirm->setPosition(Vec2(0,vs.height/3));
                    this->getParent()->addChild(confirm);
                }
                else{
                    manager->_selectedBall = bt->getTag();
                    userDef->setIntegerForKey("selectedBall", bt->getTag());
                }
                auto change = CallFunc::create([this,manager](){
                    _radioButtonGroupBall->setSelectedButton(manager->_selectedBall);
                });
                auto seq = Sequence::create(DelayTime::create(0.01f),change, NULL);
                this->runAction(seq);
            }
            
            break;
        }
            
        default:
            break;
    }
}

void SkinSelect::onChangedRadioButtonSelectBar(Ref *pSender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            auto bt = dynamic_cast<ui::RadioButton*>(pSender);
            if(bt != NULL)
            {
                auto manager = PrototypeModeManager::getInstance();
                auto userDef = UserDefault::getInstance();
                
                if(!isUnlockedBar(bt->getTag()))
                {
                    auto confirm = ConfirmationLayer::create([this,bt,manager,userDef](){
                        bt->removeAllChildrenWithCleanup(true);
                        
                        auto money = userDef->getIntegerForKey("Money");
                        money -= BAR_FEE[bt->getTag()];
                        userDef->setIntegerForKey("Money", money);
                        
                        setRadioButtonTouchEnableBar();
                        
                        auto parent = this->getParent();
                        auto shop = dynamic_cast<TitleShop*>(parent);
                        if(shop!=NULL){
                            shop->setMoneyLabel();
                        }
                        
                        std::ostringstream ostr;
                        ostr << "bar" << bt->getTag();
                        userDef->setBoolForKey(ostr.str().c_str(), true);
                        
                        manager->_selectedBar = bt->getTag();
                        userDef->setIntegerForKey("selectedBar", bt->getTag());
                        
                        _radioButtonGroupBar->setSelectedButton(bt->getTag());
                    });
                    auto vs = Director::getInstance()->getVisibleSize();
                    confirm->setPosition(Vec2(0,vs.height/3));
                    this->getParent()->addChild(confirm);
                }
                else{
                    manager->_selectedBar = bt->getTag();
                    userDef->setIntegerForKey("selectedBar", bt->getTag());
                }
                auto change = CallFunc::create([this,manager](){
                    _radioButtonGroupBar->setSelectedButton(manager->_selectedBar);
                });
                auto seq = Sequence::create(DelayTime::create(0.01f),change, NULL);
                this->runAction(seq);
            }
            break;
        }
            
            default:
            break;
    
    }
}

//引数のidのボールがアンロックされているかどうか
bool SkinSelect::isUnlockedBall(int ballId)
{
    if(IS_LOCKEDMODE)
    {
        //０と１はデフォルトでアンロックされているのでtrueを返す
        if(ballId == 0 || ballId == 1)
            return true;
        
        auto userDef = UserDefault::getInstance();
        
        std::ostringstream ostr;
        ostr << "ball" << ballId;
        
        if(userDef->getBoolForKey(ostr.str().c_str()))
            return true;
    }
    
    return false;
}

//買えないボールのボタンは押せないようにする
//買えないボールの南京錠は赤くする
//この関数はinit関数、ボールを購入した後に呼び出す必要がある
void SkinSelect::setRadioButtonTouchEnableBall()
{
    if(IS_LOCKEDMODE)
    {
        for(int i = 0; i < _radioButtonGroupBall->getNumberOfRadioButtons(); i++)
        {
            auto bt = _radioButtonGroupBall->getRadioButtonByIndex(i);
            auto radioBt = dynamic_cast<ui::RadioButton*>(bt);
            
            if(radioBt != NULL)
            {
                //もしアンロックされていないボールであったら
                if(!isUnlockedBall(radioBt->getTag()))
                {
                    auto userDef = UserDefault::getInstance();
                    auto money = userDef->getIntegerForKey("Money");
                    
                    //お金が足りない場合押せなくし、南京錠を赤くする
                    if(money < BALL_FEE[radioBt->getTag()]){
                        radioBt->setTouchEnabled(false);
                        
                        for(auto child : radioBt->getChildren())
                            child->setColor(Color3B::RED);
                    }
                    //お金が足りる場合は押せるようにする、南京錠を白くする
                    else
                    {
                        radioBt->setTouchEnabled(true);
                        for(auto child : radioBt->getChildren())
                            child->setColor(Color3B::WHITE);
                    }
                }
            }
        }
    }
}

bool SkinSelect::isUnlockedBar(int barId)
{
    if(IS_LOCKEDMODE)
    {
        if(barId == 0 || barId == 1 ||
           barId == 2 || barId == 3 ||  barId == 4)
            return true;
        
        auto userDef = UserDefault::getInstance();
        
        std::ostringstream ostr;
        ostr << "bar" << barId;
        
        if(userDef->getBoolForKey(ostr.str().c_str()))
           return true;
    }
           
           return false;
}

void SkinSelect::setRadioButtonTouchEnableBar()
{
    if(IS_LOCKEDMODE)
    {
        for(int i = 0; i < _radioButtonGroupBar->getNumberOfRadioButtons(); i++)
        {
            auto bt = _radioButtonGroupBar->getRadioButtonByIndex(i);
            auto radioBt = dynamic_cast<ui::RadioButton*>(bt);
            
            if(radioBt != NULL)
            {
                if(!isUnlockedBar(radioBt->getTag()))
                {
                    auto userDef = UserDefault::getInstance();
                    auto money = userDef->getIntegerForKey("Money");
                    
                    if(money < BAR_FEE[radioBt->getTag()]){
                        radioBt->setTouchEnabled(false);
                        
                        for(auto child : radioBt->getChildren())
                            child->setColor(Color3B::RED);
                    }
                    else{
                        radioBt->setTouchEnabled(true);
                        for(auto child : radioBt->getChildren())
                            child->setColor(Color3B::WHITE);
                    }
                }
            }
        }
    }
}
