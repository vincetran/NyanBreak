#include "TitleLayer.h"
#include "HelloWorldScene.h"
#include "Options.h"

using namespace cocos2d;
using namespace CocosDenshion;

USING_NS_CC;

CCScene* TitleLayer::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	TitleLayer *layer = TitleLayer::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool TitleLayer::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0,51,102,255)) )
	{
		return false;
	}
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *title = CCLabelTTF::labelWithString("NyanBreak", "slkscr.ttf", 64.0);
    
    title->setPosition(ccp(windowSize.width / 2, 2*windowSize.height/3));
    
    this->addChild(title, 1);
    
    CCMenuItemFont::setFontName("slkscr.ttf");
    
    CCMenuItemFont *playButton = CCMenuItemFont::itemFromString("Play", this, menu_selector(TitleLayer::playButtonAction));
    CCMenuItemFont *optionsButton = CCMenuItemFont::itemFromString("Options", this, menu_selector(TitleLayer::optionsButtonAction));
    
    CCMenu *menu = CCMenu::menuWithItems(playButton, optionsButton, NULL);

    menu->alignItemsHorizontallyWithPadding(20);
    
    menu->setPosition(ccp(windowSize.width / 2, title->getPosition().y - 1.5*title->getContentSize().height));

    this->addChild(menu, 2);

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("nyan.mp3", true);
        
	return true;
}

void TitleLayer::playButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void TitleLayer::optionsButtonAction(CCObject* pSender)
{
   CCDirector::sharedDirector()->replaceScene(Options::scene());
}