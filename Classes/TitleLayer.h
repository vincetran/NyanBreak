#ifndef __TITLELAYER_H__
#define __TITLELAYER_H__

#include "cocos2d.h"

class TitleLayer : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(TitleLayer);
    
    void playButtonAction(CCObject* pSender);
    void optionsButtonAction(CCObject* pSender);
private:

};

#endif // __TITLELAYER_H__