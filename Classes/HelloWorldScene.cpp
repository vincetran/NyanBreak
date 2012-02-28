#include "HelloWorldScene.h"

using namespace cocos2d;
using namespace CocosDenshion;
USING_NS_CC;

#define PTM_RATIO 32

bool HelloWorld::init()
{
    CCLog("HERPIERO");
    do
    {
        CCLog("In INITTIENITNITNT");
        CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(0,51,102,255)));
    }while(0);

    return true;
}

void HelloWorld::gameLogic(ccTime dt)
{
    this->addStar();
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
    this->addChild(star, 0);

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

HelloWorld::HelloWorld()
{
    setIsTouchEnabled( true );
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor::initWithColor(ccc4(0,51,102,255));   

	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	
	bool doSleep = true;
	_world = new b2World(gravity, doSleep);
    
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	
	_groundBody = _world->CreateBody(&groundBodyDef);
	
	b2PolygonShape groundBox;		
	
	groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO,0));
	_bottomFixture = _groundBody->CreateFixture(&groundBox, 0);
	
	groundBox.SetAsEdge(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
	_groundBody->CreateFixture(&groundBox, 0);
	
	groundBox.SetAsEdge(b2Vec2(0,winSize.height/PTM_RATIO), b2Vec2(0,0));
	_groundBody->CreateFixture(&groundBox, 0);
	
	groundBox.SetAsEdge(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,0));
	_groundBody->CreateFixture(&groundBox, 0);
    
	CCSprite *ball = CCSprite::spriteWithFile("rock.PNG");
    ball->setPosition(ccp(100, 100));
    ball->setTag(1);
    this->addChild(ball);
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
    ballBodyDef.userData = ball;
    
    b2Body *ballBody = _world->CreateBody(&ballBodyDef);
    
    b2CircleShape circle;
    circle.m_radius = 19.0/PTM_RATIO;
    
    // Create shape definition and add body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;
    _ballFixture = ballBody->CreateFixture(&ballShapeDef);
    
    b2Vec2 force = b2Vec2(10, 10);
    ballBody->ApplyLinearImpulse(force, ballBodyDef.position);
    
    CCSprite *paddle = CCSprite::spriteWithFile("paddle.png");
    paddle->setPosition(ccp(winSize.width/2, 50));
    this->addChild(paddle, 1);
    
    // Create paddle body
    b2BodyDef paddleBodyDef;
    paddleBodyDef.type = b2_dynamicBody;
    paddleBodyDef.position.Set(winSize.width/2/PTM_RATIO, 50/PTM_RATIO);
    paddleBodyDef.userData = paddle;
    _paddleBody = _world->CreateBody(&paddleBodyDef);
    
    // Create paddle shape
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(paddle->getContentSize().width/PTM_RATIO/2, 
                         paddle->getContentSize().height/PTM_RATIO/2);
    
    // Create shape definition and add to body
    b2FixtureDef paddleShapeDef;
    paddleShapeDef.shape = &paddleShape;
    paddleShapeDef.density = 20.0f;
    paddleShapeDef.friction = 0.5f;
    paddleShapeDef.restitution = 0.f;
    _paddleFixture = _paddleBody->CreateFixture(&paddleShapeDef);
    
    // Restrict paddle along the x axis
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(_paddleBody, _groundBody, 
                        _paddleBody->GetWorldCenter(), worldAxis);
    _world->CreateJoint(&jointDef);

    _mouseJoint = NULL;
    
    _contactListener = new MyContactListener();
    _world->SetContactListener(_contactListener);
    
    int counter=0;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 3; j++)
        {
            static int padding=20;
            CCSprite *block;
            // Create block and add it to the layer
            if(counter % 6 == 0)
                block = CCSprite::spriteWithFile("red_brick.png");
            else if(counter % 6 == 1)
                block = CCSprite::spriteWithFile("orange_brick.png");
            else if(counter % 6 == 2)
                block = CCSprite::spriteWithFile("yellow_brick.png");
            else if(counter % 6 == 3)
                block = CCSprite::spriteWithFile("green_brick.png");
            else if(counter % 6 == 4)
                block = CCSprite::spriteWithFile("blue_brick.png");
            else
                block = CCSprite::spriteWithFile("purple_brick.png");
            counter++;
            int xOffset = padding+block->getContentSize().width/2+
            ((block->getContentSize().width+padding)*i);
            int yOffset = 370-padding+block->getContentSize().height/2+
            ((block->getContentSize().height+padding)*j);
            block->setPosition(ccp(xOffset, yOffset));
            block->setTag(2);
            this->addChild(block, 1);
            
            // Create block body
            b2BodyDef blockBodyDef;
            blockBodyDef.type = b2_dynamicBody;
            blockBodyDef.position.Set(xOffset/PTM_RATIO, yOffset/PTM_RATIO);
            blockBodyDef.userData = block;
            b2Body *blockBody = _world->CreateBody(&blockBodyDef);
            
            // Create block shape
            b2PolygonShape blockShape;
            blockShape.SetAsBox(block->getContentSize().width/PTM_RATIO/2,
                                block->getContentSize().height/PTM_RATIO/2);
            
            // Create shape definition and add to body
            b2FixtureDef blockShapeDef;
            blockShapeDef.shape = &blockShape;
            blockShapeDef.density = 10.0;
            blockShapeDef.friction = 0.0;
            blockShapeDef.restitution = 0.0;
            blockBody->CreateFixture(&blockShapeDef);
        } 
    }
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("nyan.mp3", true);
    
    this->schedule(schedule_selector(HelloWorld::tick));
    this->schedule(schedule_selector(HelloWorld::gameLogic), 0.5);
}

void HelloWorld::draw()
{
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//world->DrawDebugData();
	
	// restore default GL states
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
}

void HelloWorld::tick(ccTime dt)
{

	int velocityIterations = 8;
	int positionIterations = 1;
    
	_world->Step(dt, velocityIterations, positionIterations);
	
    bool blockFound = false;
    
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
            
            if (myActor->getTag() == 1) {
                static int maxSpeed = 20;
                static int minSpeed = 10;
                
                b2Vec2 velocity = b->GetLinearVelocity();
                float32 speed = velocity.Length();
                
                if (speed > maxSpeed) {
                    b->SetLinearDamping(0.2);
                } else if (speed < maxSpeed) {
                    b->SetLinearDamping(0.0);
                }
                if(speed < minSpeed)
                {
                    b2Vec2 newVel;
                    newVel.Set(1.2*velocity.x, 1.2*velocity.y);
                    b->SetLinearVelocity(newVel);
                }
            }
            
            if (myActor->getTag() == 2) {
                blockFound = true;
            }
		}	
	}
    
    std::vector<b2Body *>toDestroy;
    std::vector<MyContact>::iterator pos;
    for(pos = _contactListener->_contacts.begin(); 
        pos != _contactListener->_contacts.end(); ++pos) {
        MyContact contact = *pos;
        
        if ((contact.fixtureA == _bottomFixture && contact.fixtureB == _ballFixture) ||
            (contact.fixtureA == _ballFixture && contact.fixtureB == _bottomFixture)) {
            GameOverScene *gameOverScene = GameOverScene::node();
            gameOverScene->getLayer()->getLabel()->setString("You Lose! :[");
            CCDirector::sharedDirector()->replaceScene(gameOverScene);
        } 
        
        b2Body *bodyA = contact.fixtureA->GetBody();
        b2Body *bodyB = contact.fixtureB->GetBody();
        if (bodyA->GetUserData() != NULL && bodyB->GetUserData() != NULL) {
            CCSprite *spriteA = (CCSprite *) bodyA->GetUserData();
            CCSprite *spriteB = (CCSprite *) bodyB->GetUserData();
            
            // Sprite A = ball, Sprite B = Block
            if (spriteA->getTag() == 1 && spriteB->getTag() == 2) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) 
                    == toDestroy.end()) {
                    toDestroy.push_back(bodyB);
                }
            }
            // Sprite B = block, Sprite A = ball
            else if (spriteA->getTag() == 2 && spriteB->getTag() == 1) {
                if (std::find(toDestroy.begin(), toDestroy.end(), bodyA) 
                    == toDestroy.end()) {
                    toDestroy.push_back(bodyA);
                }
            }        
        }                 
    }
    
    std::vector<b2Body *>::iterator pos2;
    for(pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
        b2Body *body = *pos2;     
        if (body->GetUserData() != NULL) {
            CCSprite *sprite = (CCSprite *) body->GetUserData();
            this->removeChild(sprite, true);
        }
        _world->DestroyBody(body);
    }
    
    if (!blockFound)
    {
        GameOverScene *gameOverScene = GameOverScene::node();
        gameOverScene->getLayer()->getLabel()->setString("You Win!");
        CCDirector::sharedDirector()->replaceScene(gameOverScene);
    }
    
    if (toDestroy.size() > 0)
    {
        SimpleAudioEngine::sharedEngine()->playEffect("break.mp3");
    }
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
    if (_mouseJoint != NULL) return;
    
    CCTouch *myTouch = (CCTouch *)touches->anyObject();
    CCPoint location = myTouch->locationInView(myTouch->view());
    location = CCDirector::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
    
    b2MouseJointDef md;
    md.bodyA = _groundBody;
    md.bodyB = _paddleBody;
    md.target = locationWorld;
    md.collideConnected = true;
    md.maxForce = 1000.0f * _paddleBody->GetMass();
    
    _mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
    _paddleBody->SetAwake(true);
}

void HelloWorld::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint == NULL) return;
    
    CCTouch *myTouch = (CCTouch *)touches->anyObject();
    CCPoint location = myTouch->locationInView(myTouch->view());
    location = CCDirector::sharedDirector()->convertToGL(location);
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);

    _mouseJoint->SetTarget(locationWorld);
}

void HelloWorld::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint) 
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    if (_mouseJoint) 
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }  
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::node();

    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
