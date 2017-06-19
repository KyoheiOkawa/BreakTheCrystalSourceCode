//
//  TitleShop.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/23.
//
//

#include <iomanip>
#include <sstream>
#include "Common.h"

USING_NS_CC;

bool TitleShop::init()
{
    if(!LayerColor::initWithColor(Color4B(0,0,0,200)))
        return false;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TitleShop::onTouchBegin, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(TitleShop::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TitleShop::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    _skinSelect = SkinSelect::create();
    _skinSelect->setPosition(origin);
    this->addChild(_skinSelect);
    
    _abilityStore = AbilityStore::create();
    _abilityStore->setPosition(origin);
    _abilityStore->setVisible(false);
    _abilityStore->setTouchEnabled(false);
    this->addChild(_abilityStore);
    
    auto backButton = ui::Button::create("Texture/Button/leftArrow.png");
    backButton->setScale(0.3f);
    backButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    backButton->setPosition(origin+Vec2(0,vs.height*3.0f/4.0f));
    this->addChild(backButton);
    backButton->addTouchEventListener(CC_CALLBACK_2(TitleShop::onBackButton, this));
    
    auto money = UserDefault::getInstance()->getIntegerForKey("Money");
    std::ostringstream ostr;
    ostr << std::setw(4) << std::setfill('0') << std::right << money << " BP";
    
    _moneyLabel = Label::createWithTTF(ostr.str(), USE_FONT_PATH, 80);
    _moneyLabel->setPosition(origin+Vec2(vs.width/2,backButton->getPosition().y+backButton->getContentSize().height*0.6f-20));
    this->addChild(_moneyLabel);
    
    auto toggle = ui::Button::create("Texture/Button/toggle/skin_n.png","Texture/Button/toggle/skin_p.png");
    toggle->setScale(1.0f);
    toggle->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    toggle->setPosition(origin+Vec2(vs.width,backButton->getPositionY()));
    this->addChild(toggle);
    toggle->addTouchEventListener(CC_CALLBACK_2(TitleShop::onToggleChanged, this));
    _isToggleOn = false;
    
    return true;
}

void TitleShop::onBackButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch(type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            this->removeFromParentAndCleanup(true);
            
            break;
        }
            
        default:
            break;
    }
}

void TitleShop::onToggleChanged(Ref *pSender,ui::Widget::TouchEventType type)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    switch(type)
    {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            
            auto toggle = dynamic_cast<ui::Button*>(pSender);
            if(!_isToggleOn){
                _isToggleOn = true;
                toggle->loadTextures("Texture/Button/toggle/ability_n.png","Texture/Button/toggle/ability_p.png");
                _skinSelect->setVisible(false);
                _skinSelect->setEnabled(false);
                _abilityStore->setVisible(true);
                _abilityStore->setTouchEnabled(true);
            }
            else{
                _isToggleOn = false;
                toggle->loadTextures("Texture/Button/toggle/skin_n.png","Texture/Button/toggle/skin.png");
                _skinSelect->setVisible(true);
                _skinSelect->setEnabled(true);
                _abilityStore->setVisible(false);
                _abilityStore->setTouchEnabled(false);
            }
            
            break;
        }
        default:
            break;
    }
}

//マネーラベルの更新関数
void TitleShop::setMoneyLabel()
{
    auto money = UserDefault::getInstance()->getIntegerForKey("Money");
    std::ostringstream ostr;
    ostr << std::setw(4) << std::setfill('0') << std::right << money << "BP";
    
    _moneyLabel->setString(ostr.str());
}

bool TitleShop::onTouchBegin(Touch* touch, Event* event)
{
    return true;
}

void TitleShop::onTouchMoved(Touch* touch, Event* event)
{
    
}

void TitleShop::onTouchEnded(Touch* touch, Event* event)
{
    
}
