#include "BrickBreak.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "PlayerWin.h"
USING_NS_CC;

Scene* BrickBreak::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//Vect gravity(0.0f, 0.0f); 
	//scene->getPhysicsWorld()->setGravity(gravity);
    
    // 'layer' is an autorelease object
    auto layer = BrickBreak::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

	
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BrickBreak::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
    /////////////////////////////
	
	edgeSp = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->getShape(0)->setRestitution(1.0f);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setDensity(1.0f);
	edgeSp->setPosition(Point((visibleSize.width / 2)+origin.x, (visibleSize.height / 2))); 
	edgeSp->setPhysicsBody(boundBody); 
	boundBody->setContactTestBitmask(0x000001); 
	this->addChild(edgeSp); 
	edgeSp->setTag(0); 

	/*	Tag guide
		0 - window
		1 - ball
		2 - paddle
		3 - brick
		4 - rock
		5 - metal
	*/
	
	brick = new Brick();
	bricksLeft = 0;
	for (int i = 0; i < 8; i++) {
		static int pad = 15;
		int yOffset = (16-i) * 30;
		for (int j = 0; j < 7; j++) {
			if (i== 0 ||i==5|| i==7) {
				brick->spawnBrick(this, 1, j, yOffset);
				bricksLeft++;
			}
			else if (i== 1 || i==4||i==6) {
				brick->spawnBrick(this, 2, j, yOffset);
				bricksLeft++;
			}
			else if (i == 2 || i == 3) {
				brick->spawnBrick(this, 3, j, yOffset);
				bricksLeft++;
			}
		}
	}


	PaddleSprite = Sprite::create("spr_Paddle.png");
	PaddleSprite -> setPosition(Point((visibleSize.width/2) + origin.x,origin.y+15));	
	auto paddleBody = PhysicsBody::createBox(PaddleSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	
	paddleBody->getShape(0)->setRestitution(1.0f);
	paddleBody->getShape(0)->setFriction(0.0f);
	paddleBody->getShape(0)->setDensity(10.0f);
	paddleBody->setGravityEnable(false);
	PaddleSprite->setPhysicsBody(paddleBody);
	paddleBody->setContactTestBitmask(0x000001); 
	PaddleSprite->setTag(2);
	paddleBody->setDynamic(false);
	this->addChild(PaddleSprite,75);
	playerLife = 3;

	ball = new Ball(this);

	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event) {

		if (keys.find(keycode) == keys.end()){
			keys[keycode] = std::
				chrono::high_resolution_clock::now();
		}
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE && !ball->isLaunched()) {
			ball->setIsLaunched(true);
			ball->setForce(110000.0f,110000.0f);

		}
	};

	eventListener->onKeyReleased = [this](EventKeyboard::KeyCode keycode, Event* event) {
		keys.erase(keycode);
	};


	auto contactDispatch = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BrickBreak::hasCollided, this);
	contactDispatch->addEventListenerWithSceneGraphPriority(contactListener, this);

	
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, PaddleSprite);

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Collide.wav");
	this->schedule(schedule_selector(BrickBreak::checkWin),0);
	this->scheduleUpdate();
	
	
	return true;
}


bool BrickBreak::isKeyPressed(cocos2d::EventKeyboard::KeyCode keycode) {
	if (keys.find(keycode) != keys.end())
		return true;
	return false;

}

void BrickBreak::update(float delta) {
	Vec2 bPos = ball->getSpritePosition();
	auto pos = PaddleSprite->getPosition();
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		if (pos.x>76) {
			pos.x -= 380 * delta;
			bPos.x -= 380 * delta;
			PaddleSprite->setPosition(pos);
			if(!ball->isLaunched())
				ball->setSpritePosition(bPos);
		}
	}
	else if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		if (pos.x < 645) {
			pos.x += 380 * delta;
			bPos.x += 380 * delta;
			PaddleSprite->setPosition(pos);
			if(!ball->isLaunched())
				ball->setSpritePosition(bPos);
		}
	}
	
}

bool BrickBreak::hasCollided(PhysicsContact& collide) {

	auto sprite1 = (Sprite*)collide.getShapeA()->getBody()->getNode();
	auto sprite2 = (Sprite*)collide.getShapeB()->getBody()->getNode();

	//sprite2->
	int tag1 = sprite1->getTag();
	int tag2 = sprite2->getTag();

	if (tag1 == 3) {
		bricksLeft--;
		this->removeChild(sprite1, true);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Collide.wav");

	}

	else if (tag2 == 3) {
		this->removeChild(sprite2,true);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Collide.wav");

	}
	else if (tag2 == 4||tag1==4) {
		sprite2->setTexture("spr_Brick.png");
		sprite2->setTag(3);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Collide.wav");

	}
	else if (tag2==5||tag1==5) {
		sprite2->setTexture("spr_Rock.png");
		sprite2->setTag(4);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Collide.wav");

	}

	if ((tag1 == 0 || tag2 == 0 )&& ball->getSpritePositionY() <= (PaddleSprite->getPositionY()+10)) {
		 CCLOG("HELLO");
		 CCLOG("%f < %f", ball->getSpritePositionY(),PaddleSprite->getPositionY());
		 //this->scheduleOnce(schedule_selector(BrickBreak::refreshPaddle),0.0);
		 if (playerLife > 0) {
			 playerLife--;
			 if (playerLife == 2)
				 PaddleSprite->setTexture("spr_Paddle2.png");
			 else if (playerLife == 1)
				 PaddleSprite->setTexture("spr_Paddle3.png");
			 else if (playerLife == 0)
				 PaddleSprite->setTexture("spr_Paddle4.png");

			 this->scheduleOnce(schedule_selector(BrickBreak::refreshPaddle), 0.0);
		 }
		 else {
		 auto scene = GameOverScene::createScene();
		 Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
		 }
	}

	return true;
}
void BrickBreak::checkWin(float delta) {
	bool isWin = true;

	Vector<PhysicsBody *> bricks = bworld->getAllBodies();

	for each(PhysicsBody* body in bricks) {
		if (body->getNode()->getTag() == 3 || body->getNode()->getTag() == 4 || body->getNode()->getTag() == 5)
			isWin = false;
	}
	if (isWin == true) {
		auto scene = PlayerWin::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	}


}
void BrickBreak::refreshPaddle(float delta) {
	ball->setSpriteVelocity();
	Vec2 newPos = PaddleSprite->getPosition();
	newPos.y = PaddleSprite->getPositionY() + 25;
	ball->setIsLaunched(false);
	ball->setSpritePosition(newPos);
}

void GoToGameOverScene(cocos2d::Ref *sender) {
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene));
	
}

void BrickBreak::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

std::map<cocos2d::EventKeyboard::KeyCode,
	std::chrono::high_resolution_clock::time_point> BrickBreak::keys;
