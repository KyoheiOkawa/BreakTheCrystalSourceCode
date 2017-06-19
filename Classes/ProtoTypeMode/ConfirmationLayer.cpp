//
//  ConfirmationLayer.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/27.
//
//

#include "Common.h"

USING_NS_CC;

bool ConfirmationLayer::init(std::function<void()> func)
{
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto vs = Director::getInstance()->getVisibleSize();
    
    if(!LayerColor::initWithColor(Color4B(200, 0, 0,220), vs.width, vs.height/3))
        return false;
    
    _parchaceFunc = func;
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(ConfirmationLayer::onTouchBegin, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(ConfirmationLayer::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(ConfirmationLayer::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    auto ownSize = this->getContentSize();
    
    auto label = Label::createWithTTF("Really Buy?", USE_FONT_PATH, 60);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    label->setPosition(Vec2(ownSize.width/2,ownSize.height-label->getContentSize().height));
    this->addChild(label);
    
    auto yes = ui::Button::create("Texture/Button/yes.png");
    yes->setAnchorPoint(Vec2::ZERO);
    yes->setPosition(Vec2(50,50));
    yes->addTouchEventListener(CC_CALLBACK_2(ConfirmationLayer::onYesButton, this));
    this->addChild(yes);
    
    auto no = ui::Button::create("Texture/Button/no.png");
    no->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    no->setPosition(Vec2(ownSize.width,0)+Vec2(-50,50));
    no->addTouchEventListener(CC_CALLBACK_2(ConfirmationLayer::onNoButton, this));
    this->addChild(no);
    
    return true;
}

ConfirmationLayer* ConfirmationLayer::create(std::function<void()> func)
{
    ConfirmationLayer *pRet = new(std::nothrow) ConfirmationLayer();
    if (pRet && pRet->init(func))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool ConfirmationLayer::onTouchBegin(Touch* touch, Event* event)
{
    return true;
}
void ConfirmationLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void ConfirmationLayer::onTouchEnded(Touch* touch, Event* event)
{
    
}

void ConfirmationLayer::onYesButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
        {
            criadx2le::playCueById(SE_BUTTON_OFF);
            _parchaceFunc();
            this->removeFromParentAndCleanup(true);
            break;
        }
        default:
            break;
    }
}

void ConfirmationLayer::onNoButton(Ref* pSender, ui::Widget::TouchEventType type)
{
    switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            criadx2le::playCueById(SE_BUTTON_ON);
            break;
        case ui::Widget::TouchEventType::ENDED:
            criadx2le::playCueById(SE_BUTTON_OFF);
            this->removeFromParentAndCleanup(true);
            break;
            
        default:
            break;
    }
}
