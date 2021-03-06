#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "PluginVungle/PluginVungle.h"

class HelloWorld : public cocos2d::Layer, public sdkbox::VungleListener
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
    void createTestMenu();

    void onShowVideo(cocos2d::Ref* sender);
    void onShowReward(cocos2d::Ref* sender);

    int _coin;
    cocos2d::Label *_coinLabel;

    void onVungleCacheAvailable();
    void onVungleStarted();
    void onVungleFinished();
    void onVungleAdViewed(bool isComplete);
    void onVungleAdReward(const std::string& name);
};

#endif // __HELLOWORLD_SCENE_H__
