//
//  AbilityStore.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/25.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"

USING_NS_CC;

bool AbilityStore::init()
{
    if(!Layer::init())
        return false;
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    auto userDef = UserDefault::getInstance();
    
    auto scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(false);
    scrollView->setPosition(Vec2::ZERO);
    this->addChild(scrollView);
    
    auto abilityLayer = LayerColor::create(Color4B(0, 0, 0, 0), vs.width, vs.height*2.0f/4.0f);
    abilityLayer->setPosition(Vec2::ZERO);
    
    
    auto ballSize = Label::createWithTTF("BallSize", USE_FONT_PATH , 60);
    ballSize->setColor(Color3B::WHITE);
    ballSize->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    ballSize->enableOutline(Color4B::BLACK,3);
    ballSize->setHorizontalAlignment(TextHAlignment::LEFT);
    ballSize->setPosition(Vec2(20,vs.height*3.0f/4.0f-30));
    this->addChild(ballSize);
    
    auto subBallLife = Label::createWithTTF("SubBall", USE_FONT_PATH, 60);
    subBallLife->setColor(Color3B::WHITE);
    subBallLife->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    subBallLife->enableOutline(Color4B::BLACK,3);
    subBallLife->setHorizontalAlignment(TextHAlignment::LEFT);
    subBallLife->setPosition(ballSize->getPosition()+Vec2(0,-ballSize->getContentSize().height));
    this->addChild(subBallLife);
    
    auto timePlus = Label::createWithTTF("Timecrys", USE_FONT_PATH, 60);
    timePlus->setColor(Color3B::WHITE);
    timePlus->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    timePlus->enableOutline(Color4B::BLACK,3);
    timePlus->setHorizontalAlignment(TextHAlignment::LEFT);
    timePlus->setPosition(subBallLife->getPosition()+Vec2(0,-subBallLife->getContentSize().height));
    this->addChild(timePlus);
    
    auto explosion = Label::createWithTTF("Explosion", USE_FONT_PATH, 60);
    explosion->setColor(Color3B::WHITE);
    explosion->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    explosion->enableOutline(Color4B::BLACK,3);
    explosion->setHorizontalAlignment(TextHAlignment::LEFT);
    explosion->setPosition(timePlus->getPosition()+Vec2(0,-timePlus->getContentSize().height));
    this->addChild(explosion);
    
    for(int i = 0; i < 4; i++){
        std::ostringstream ostr;
        ostr << "ability" << i;
        
        auto level = userDef->getIntegerForKey(ostr.str().c_str(),1);
        ostr.str("");
        
        ostr << "Lv." << std::setw(2) << std::setfill('0') << std::right << level;
        if(level == 10){
            ostr.str("");
            ostr << "Lv.MAX";
        }
        
        _level[i] = Label::createWithTTF(ostr.str(), USE_FONT_PATH, 60);
    }
    
    int i = 0;
    for(auto lb : _level){
        lb->setColor(Color3B::WHITE);
        lb->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        lb->setHorizontalAlignment(TextHAlignment::LEFT);
        lb->setPosition(Vec2(vs.width-230,ballSize->getPositionY()-i*ballSize->getContentSize().height));
        lb->enableOutline(Color4B::BLACK,3);
        this->addChild(lb);
        i++;
    }
    
    
    _abilityBt[0] = ui::Button::create("Texture/Button/abilityBallSize.png");
    _abilityBt[1] = ui::Button::create("Texture/Button/abilitySubBall.png");
    _abilityBt[2] = ui::Button::create("Texture/Button/abilityTime.png");
    _abilityBt[3] = ui::Button::create("Texture/Button/abilityExplosion.png");
    
    
    i = 0;
    for(auto bt : _abilityBt){
        float ofset = 80;
        bt->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
        bt->setScale(0.6f);
        
        if(i % 2 == 0){
            bt->setPosition(Vec2(vs.width/2-160,abilityLayer->getContentSize().height -ofset - bt->getContentSize().height*bt->getScaleX()*(i/2) - ofset*(i/2)));
        }
        else{
            bt->setPosition(Vec2(vs.width/2+160,abilityLayer->getContentSize().height -ofset - bt->getContentSize().height*(i/2)*bt->getScaleX() - ofset*(i/2)));
        }
        abilityLayer->addChild(bt);
        bt->setTag(i);
        bt->addTouchEventListener(CC_CALLBACK_2(AbilityStore::onAbilityButton, this));
        
        auto value = Label::createWithTTF("10BP", USE_FONT_PATH, 60);
        value->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
        value->setPosition(Vec2(bt->getContentSize().width/2,30));
        bt->addChild(value);
        
        i++;
    }
    setLevelBtTouchEnable();
    
    scrollView->addChild(abilityLayer);
    
    scrollView->setInnerContainerSize(abilityLayer->getContentSize());
    
    scrollView->setContentSize(Size(abilityLayer->getContentSize().width,vs.height*2.0f/4.0f));

    setLevelBtTouchEnable();
    
    return true;
}

void AbilityStore::onAbilityButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    auto bt = dynamic_cast<ui::Button*>(pSender);
    auto userDef = UserDefault::getInstance();
    auto parent = this->getParent();
    auto titleShop = dynamic_cast<TitleShop*>(parent);
    
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            if(bt != NULL)
            {
                auto confirm = ConfirmationLayer::create([this,userDef,bt,titleShop](){
                    std::ostringstream ostr;
                    ostr << "ability" << bt->getTag();
                    
                    auto level = userDef->getIntegerForKey(ostr.str().c_str(),1);
                    level++;
                    userDef->setIntegerForKey(ostr.str().c_str(), level);
                    
                    auto money = userDef->getIntegerForKey("Money");
                    money -= 10;
                    userDef->setIntegerForKey("Money", money);
                    
                    if(titleShop != NULL){
                        titleShop->setMoneyLabel();
                    }
                    
                    setLevelLabelString(bt->getTag());
                    setLevelBtTouchEnable();
                });
                auto vs = Director::getInstance()->getVisibleSize();
                confirm->setPosition(Vec2(0,vs.height/3));
                this->getParent()->addChild(confirm);
            }
            
            break;
        }
            
        default:
            break;
    }
}

void AbilityStore::setLevelLabelString(int index)
{
    auto userDef = UserDefault::getInstance();
    
    std::ostringstream ostr;
    ostr << "ability" << index;
    
    auto level = userDef->getIntegerForKey(ostr.str().c_str(), 1);
    ostr.str("");
    
    ostr << "Lv." << std::setw(2) << std::setfill('0') << std::right << level;
    
    if(level == 10){
        ostr.str("");
        ostr << "Lv.MAX";
    }
    
    _level[index]->setString(ostr.str());
}

void AbilityStore::setLevelBtTouchEnable()
{
    auto userDef = UserDefault::getInstance();
    auto money = userDef->getIntegerForKey("Money");
    
    for(auto bt : _abilityBt){
        auto dbt = dynamic_cast<ui::Button*>(bt);
        if(dbt != NULL){
            std::ostringstream ostr;
            ostr << "ability" << dbt->getTag();
            auto level = userDef->getIntegerForKey(ostr.str().c_str());
            
            if(money < 10 || level == 10){
                dbt->setTouchEnabled(false);
                dbt->setColor(Color3B::GRAY);
                for(auto chil : dbt->getChildren()){
                     auto value = dynamic_cast<Label*>(chil);
                    if(value != NULL){
                        value->setColor(Color3B(100,100,100));
                    }
                }
            }
            else{
                dbt->setTouchEnabled(true);
                dbt->setColor(Color3B::WHITE);
                for(auto chil : dbt->getChildren()){
                    auto value = dynamic_cast<Label*>(chil);
                    if(value != NULL){
                        value->setColor(Color3B::WHITE);
                    }
                }
            }
        }
    }
}
