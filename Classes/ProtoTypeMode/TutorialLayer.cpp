//
//  TutorialLayer.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/28.
//
//

#include <iomanip>
#include <ostream>
#include "Common.h"

USING_NS_CC;

bool TutorialLayer::init()
{
    if(!LayerColor::initWithColor(Color4B(0,0,0,150)))
        return false;
    
    auto vs = Director::getInstance()->getVisibleSize();
    
    ///フリックする方向を示す
    auto flickDir = Sprite::create("Texture/Other/flickChange.png");
    flickDir->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    flickDir->setPosition(Vec2(vs.width/2,0));
    flickDir->setScale(vs.width/flickDir->getContentSize().width);
    this->addChild(flickDir);
    auto faction1 = TintTo::create(0.5f, Color3B(150,150,150));
    auto faction2 = TintTo::create(0.5f, Color3B::WHITE);
    auto fseq = Sequence::create(faction1,faction2, NULL);
    auto frepeat = RepeatForever::create(fseq);
    flickDir->runAction(frepeat);
    
    ///FlickToChangePageラベルを表示させる
    auto flickTo = Label::createWithTTF("Flick To Change Page", USE_FONT_PATH, 30);
    flickTo->setPosition(Vec2(vs.width/2,flickDir->getContentSize().height*flickDir->getScale()/2));
    this->addChild(flickTo);
    
    ///ページビューを作成
    auto _pageView = ui::PageView::create();
    _pageView->setContentSize(Size(vs.width,vs.height));
    _pageView->setPosition(Vec2::ZERO);
    this->addChild(_pageView);
    
    auto subLayer = Layer::create();
    this->addChild(subLayer);
    
    auto backButton = ui::Button::create("Texture/Button/leftArrow.png");
    backButton->setScale(0.3f);
    backButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backButton->setPosition(Vec2(0,vs.height-100));
    subLayer->addChild(backButton);
    backButton->addTouchEventListener(CC_CALLBACK_2(TutorialLayer::onBackButton, this));
    
    
    //遊び方説明スライドを配置
    for (int i = 0; i < 5; i++) {
        
        std::ostringstream ostr;
        ostr << "Texture/Tutorial/Tutorial" << i + 1 << ".png";
        
        auto imageView = ui::ImageView::create(ostr.str());
        imageView->setScale(0.8f);
        auto _layout = ui::Layout::create();
        _layout->setContentSize(_pageView->getContentSize());
        imageView->setPosition(_layout->getContentSize() / 2);
        _layout->addChild(imageView);
        _pageView->insertPage(_layout, i);
        
    }
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TutorialLayer::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void TutorialLayer::onBackButton(Ref *pSender, ui::Widget::TouchEventType type)
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

bool TutorialLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
