#include "Options.h"
#include "TitleLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

CCScene* Options::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	Options *layer = Options::node();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool Options::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0,51,102,255)) )
	{
		return false;
	}
    
    // Get window size
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenuItemFont::setFontName("slkscr.ttf");
    
    CCMenuItemFont *backButton = CCMenuItemFont::itemFromString("Back", this, menu_selector(Options::backButtonAction));

    CCMenuItem *musicOn = CCMenuItemFont::itemFromString("Music: On");
    CCMenuItem *musicOff = CCMenuItemFont::itemFromString("Music: Off");

    CCMenuItemToggle *musicToggle  = CCMenuItemToggle::itemWithTarget(this, menu_selector(Options::musicToggleAction),musicOff,musicOn,NULL);

    CCMenu *musicMenu = CCMenu::menuWithItems(musicToggle, NULL);
    
    CCMenu *backMenu = CCMenu::menuWithItems(backButton, NULL);

    musicMenu->alignItemsHorizontallyWithPadding(20);

    musicMenu->setPosition(ccp(windowSize.width / 2, windowSize.height/2));

    backMenu->alignItemsHorizontallyWithPadding(20);
    
    backMenu->setPosition(ccp(windowSize.width / 10, 50));

    this->addChild(backMenu, 2);
    this->addChild(musicMenu, 2);
        
	return true;
}

void Options::backButtonAction(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(TitleLayer::scene());
}

void Options::musicToggleAction(CCObject* pSender)
{
	L= (CCMenuItemToggle*)pSender;
	int i=(L->getSelectedIndex());
	if(i == 0)
	{
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(false);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("nyan.mp3", true);
	}
}
