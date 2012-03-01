#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include "cocos2d.h"
USING_NS_CC;

class Options : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Options);
    
    void backButtonAction(CCObject* pSender);
    void musicToggleAction(CCObject* pSender);

    CCMenuItemToggle *L;
private:

};

#endif // __TITLELAYER_H__