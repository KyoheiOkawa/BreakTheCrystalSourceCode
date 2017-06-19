#include "AppDelegate.h"
#include "ProtoTypeMode/TitleScene.hpp"
#include "NativeCodeLauncher.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size smallResolutionSize = cocos2d::Size(320, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
    criadx2le::finalize();
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("BreakTheCrystal");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
    
    criadx2le::initialize();

    const auto frameSize = glview->getFrameSize();
    auto designSize = designResolutionSize;
    
    if(Application::getInstance()->getTargetPlatform() == Platform::OS_IPAD)
    {
        designSize = cocos2d::Size(768.0f,1136.0f);
    }
    
    glview->setDesignResolutionSize(designSize.width ,designSize.height, ResolutionPolicy::SHOW_ALL);
    director->setContentScaleFactor(designSize.width/director->getWinSize().width);
    
    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = TitleScene::createScene();

    // run
    director->runWithScene(scene);
    
    Cocos2dExt::NativeCodeLauncher::loginGameCenter();

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    criAtomEx_StopSound_IOS();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    criAtomEx_StartSound_IOS();
#endif
}
