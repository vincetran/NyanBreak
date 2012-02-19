#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	bool bRet=false;
	do{
		if ( !CCLayerColor::initWithColor(ccc4(0,51,102,255)))
		{
			return false;
		}

		CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
											"CloseNormal.png",
											"CloseSelected.png",
											this,
											menu_selector(HelloWorld::menuCloseCallback) );
		pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

		// create menu, it's an autorelease object
		CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
		pMenu->setPosition( CCPointZero );
		this->addChild(pMenu, 1);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *paddle = CCSprite::spriteWithFile("mrnyan.png", CCRectMake(0,0,167,40));
		paddle->setPosition( ccp(winSize.width/2, winSize.height/9));
		this->addChild(paddle);

		CCSprite *block = CCSprite::spriteWithFile("red_brick.png", CCRectMake(0,0,113,15));
		block->setPosition(ccp(block->getContentSize().width/2+20, 700));
		this->addChild(block);

		bRet=true;
	}while(0);
	this->schedule(schedule_selector(HelloWorld::gameLogic), 0.5);
	return bRet;
}

void HelloWorld::addStar()
{
	CCSprite *star = CCSprite::spriteWithFile("star.png", CCRectMake(0,0,40,40));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minY = star->getContentSize().height/2;
	int maxY = winSize.height - star-> getContentSize().height/2;
	int rangeY = maxY - minY;
	int actualY = (rand() % rangeY) + minY;
	star->setPosition(ccp(winSize.width + (star->getContentSize().width/2), actualY));
	this->addChild(star);

	int minDuration = (int)2.0;
	int maxDuration = (int)4.0;
	int rangeDuration = maxDuration - minDuration;
	int actualDuration = (rand() % rangeDuration) + minDuration;

	CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration((ccTime)actualDuration, ccp(0-star->getContentSize().width/2, actualY));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	star->runAction(CCSequence::actions(actionMove,actionMoveDone, NULL));
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
}

void HelloWorld::gameLogic(ccTime dt)
{
	this->addStar();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
