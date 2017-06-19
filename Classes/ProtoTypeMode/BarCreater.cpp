//
//  BarCreater.cpp
//  BreakTheCrystal
//
//  Created by 大川恭平 on 2017/02/06.
//
//

#include "Common.h"

USING_NS_CC;

bool BarCreater::init()
{
    auto manager = PrototypeModeManager::getInstance();
    
    if(!Layer::init())
        return false;
    
    //ガイドバーのテクスチャ
    auto guidBarTex = Director::getInstance()->getTextureCache()->getTextureForKey(manager->_barTexturePath.at(manager->_selectedBar));
    
    _guideBar = Sprite::createWithTexture(guidBarTex);
    _guideBar->setOpacity(0);
    this->addChild(_guideBar);
    
    this->setName("BarCreater");
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(BarCreater::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BarCreater::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BarCreater::onTouchEnded, this);
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool BarCreater::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

//ここではガイド線の作成
void BarCreater::onTouchMoved(Touch* touch, Event* event)
{
    setGuideBar(touch);
}

//ここではバーの生成処理
void BarCreater::onTouchEnded(Touch* touch, Event* evet)
{
    createBar(touch);
}

void BarCreater::setGuideBar(Touch* touch)
{
    auto mainScene = dynamic_cast<MainScene*>(this->getParent());
    
    if((mainScene->GetState() == GameState::PLAYING))
    {
        float length = 0;
        Vec2 pos = Vec2::ZERO;
        float rotation = 0;
        
        calBarLenPosRot(length, pos, rotation, touch);
        
        _guideBar->setPosition(pos);
        _guideBar->setRotation(rotation);
        _guideBar->setScale(length/_guideBar->getContentSize().width,0.5f);
        
        _guideBar->setOpacity(GUIDEBAR_OPACITY);
        
        //この長さでは生成できないことを伝えるために
        //バーの長さが最小値を超えていなかったらガイドバーを赤色にする
        if(!isReachedMinLength(length)){
            _guideBar->setColor(Color3B(255,0,0));
        }else{
            _guideBar->setColor(Color3B(255,255,255));
        }
    }
}

void BarCreater::createBar(Touch* touch)
{
    auto mainScene = dynamic_cast<MainScene*>(this->getParent());
    
    if((mainScene->GetState() == (int)GameState::PLAYING))
    {
        _guideBar->setOpacity(0);
        _guideBar->setColor(Color3B(255,255,255));
        
        auto parent = this->getParent();
        
        float length = 0;
        Vec2 pos = Vec2::ZERO;
        float rotation = 0;
        
        calBarLenPosRot(length, pos, rotation, touch);
        
        //バーの長さが最小値を超えていたら生成する
        if(isReachedMinLength(length)){
            auto bar = Bar::create(length, pos, rotation);
            parent->addChild(bar,8);
        }
    }
}

//引数posにはバー生成の際の座標を渡す
//もしその座標が壁の内側ではなかった場合posをバーの内側になるように変更する
void BarCreater::limitBarCreateArea(Vec2& pos)
{
    Vec2 origin;
    Size vs;
    PrototypeModeManager::MultiResolution(origin, vs);
    
    //壁の幅
    float wallLength = 60.0f;
    float TopWallLength = 160.0f;
    
    if(pos.x <= origin.x + wallLength){
        pos.x = origin.x + wallLength;
    }
    else if(pos.x >= origin.x + vs.width - wallLength){
        pos.x = origin.x + vs.width - wallLength;
    }
    if(pos.y <= origin.y + wallLength){
        pos.y = origin.y + wallLength;
    }
    else if(pos.y >= origin.y + vs.height - TopWallLength){
        pos.y = origin.y + vs.height - TopWallLength;
    }
    
}

//バーの生成、バーのガイドを引くときに必要な計算をこの関数にまとめておく
//onTouchMovedとonTouchEndedで同じ計算をするため
//引数にlength,pos,rotationを参照で渡してこの関数の中で書き換える
void BarCreater::calBarLenPosRot(float &length, Vec2 &pos, float &rotation,Touch* touch)
{
    Vec2 end = touch->getLocation();
    limitBarCreateArea(end);
    Vec2 start = touch->getStartLocation();
    limitBarCreateArea(start);
    Vec2 dir = end - start;
    dir.normalize();
    
    pos = (end+start)/2.0f;
    length = end.getDistance(start);
    rotation = MATH_RAD_TO_DEG(Vec2::angle(Vec2(1.0f,0), dir));
    
    //タッチ開始地点のY座標より話した時のY座標の方が上にあった場合
    //角度の符号を反転する
    if(end.y > start.y)
        rotation *= -1;
}

//バー生成する際長さが最小値を超えてるか判定する関数
//引数には生成する予定のバーの長さを渡す
//最小値を超えていればtrueそうでなければfalseを返す
bool BarCreater::isReachedMinLength(float length)
{
    if(length <= MIN_BAR_LENGTH)
        return false;
    
    return true;
}
