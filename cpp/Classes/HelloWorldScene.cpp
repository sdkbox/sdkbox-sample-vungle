
#include "HelloWorldScene.h"
#include "PluginVungle/PluginVungle.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    MenuItemFont::setFontName("sans");
    Size size = Director::getInstance()->getWinSize();

    sdkbox::PluginVungle::setListener(this);
    sdkbox::PluginVungle::setDebug(true);

    auto menu = Menu::create(MenuItemFont::create("show video", CC_CALLBACK_1(HelloWorld::onShowVideo, this)),
                             MenuItemFont::create("show reward", CC_CALLBACK_1(HelloWorld::onShowReward, this)),
                             NULL);

    menu->alignItemsVerticallyWithPadding(5);
    menu->setPosition(Vec2(size.width/2, size.height/2));
    addChild(menu);
}

void HelloWorld::onShowVideo(cocos2d::Ref* sender)
{
    sdkbox::PluginVungle::show("video");
    CCLOG("sdkbox::PluginVungle::show(\"video\")");
}

void HelloWorld::onShowReward(cocos2d::Ref* sender)
{
    sdkbox::PluginVungle::show("reward");
    CCLOG("sdkbox::PluginVungle::show(\"reward\")");
}

void HelloWorld::onVungleCacheAvailable()
{
    CCLOG("onVungleCacheAvailable");
}

void HelloWorld::onVungleStarted()
{
    CCLOG("onVungleStarted");
}

void HelloWorld::onVungleFinished()
{
    CCLOG("onVungleFinished");
}

void HelloWorld::onVungleAdViewed(bool isComplete)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        CCLOG("onVungleAdViewed: %s", isComplete ? "complete" : "not complete");
    });
}

void HelloWorld::onVungleAdReward(const std::string& name)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        CCLOG("onVungleAdReward: %s", name.c_str());
    });
}
