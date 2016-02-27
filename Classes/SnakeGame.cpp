#include "SnakeGameScene.h"

USING_NS_CC;

Scene* SnakeGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SnakeGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SnakeGameScene::init()
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
	
	
	SnakeSprite = Sprite::create("spr_Snake.png");
	this->_tail = Vector<cocos2d::Sprite *>{};
	foodNum = 0;

	SnakeSprite -> setPosition(Point((visibleSize.width/2) + origin.x,(visibleSize.height/2)+origin.y));
	

	this->addChild(SnakeSprite,75);
	//this->addChild(FoodSprite,50);
	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keycode, Event* event) {
		Vec2 loc = event->getCurrentTarget()->getPosition();
		

		switch (keycode) {

		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			// direction = keycode; break;
			if (pDir != 2) {
				dir = 1; pDir = 1; 
			}
			
			break;

		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			//event->getCurrentTarget() -> setPosition(++loc.x, loc.y); break;
			if (pDir != 1) {
				dir = 2; pDir = 2; 
			}break;

		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		//	event->getCurrentTarget()->setPosition(loc.x, ++loc.y); break;
			if (pDir != 4) {
				dir = 3; pDir = 3; 
			}break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		//	event->getCurrentTarget()->setPosition(loc.x, --loc.y); break;
			if (pDir != 3) {
				dir = 4; pDir = 4;  
			}break;
		case EventKeyboard::KeyCode::KEY_SPACE:
		{
			this->removeChildByTag(0);
			foodNum = 0;
		} break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, SnakeSprite);

	
	this->scheduleUpdate();
	this->schedule(schedule_selector(SnakeGameScene::SpawnFood),2);
	
	return true;
}

void SnakeGameScene::update(float delta) {
	pos = SnakeSprite->getPosition();
	
	speed = 100;
	Rect snakeRec = SnakeSprite->getBoundingBox();
	
	/*pos.x -= speed * delta;
	if (pos.x < 0 - (SnakeSprite->getBoundingBox().size.width / 2))
		pos.x = this->getBoundingBox().getMaxX() + SnakeSprite->getBoundingBox().size.width / 2;

	SnakeSprite->setPosition(pos);*/
	switch (dir) {

	case 1:
	{	pos.x -= speed * delta;
	if (pos.x < 0 - (SnakeSprite->getBoundingBox().size.width / 2))
		pos.x = this->getBoundingBox().getMaxX() + SnakeSprite->getBoundingBox().size.width / 2;

	SnakeSprite->setPosition(pos);

	if (this->_tail.size()>0) {
		int x;

		for (x = this->_tail.size() - 1; x >= 0; x--) {
			auto tailPos = this->_tail.at(x)->getPosition();
			
			tailPos.x -= (speed * delta);
			if (tailPos.x < 0 - (this->_tail.at(x)->getBoundingBox().size.width / 2))
				tailPos.x = this->getBoundingBox().getMaxX() + this->_tail.at(x)->getBoundingBox().size.width / 2;


			this->_tail.at(x)->setPosition(tailPos);
		}

	}

	}
	break;
	case 2:
	{	pos.x += speed * delta;
	if (pos.x > 480 + (SnakeSprite->getBoundingBox().size.width / 2))
		pos.x = 0 - SnakeSprite->getBoundingBox().size.width / 2;

	if (this->_tail.size() > 0) {
		int x;

		for (x = this->_tail.size() - 1; x >= 0; x--) {
			auto tailPos = this->_tail.at(x)->getPosition();

			tailPos.x += (speed * delta);
			if (tailPos.x > 480 + (this->_tail.at(x)->getBoundingBox().size.width / 2))
				tailPos.x = 0 - this->_tail.at(x)->getBoundingBox().size.width / 2;


			this->_tail.at(x)->setPosition(tailPos);
		}

	}

	SnakeSprite->setPosition(pos);
	
	break;
	}
	case 3:
	{	pos.y += speed * delta;
	if (pos.y > 320 + (SnakeSprite->getBoundingBox().size.width / 2))
		pos.y = 0 - SnakeSprite->getBoundingBox().size.width / 2;
	if (this->_tail.size() > 0) {
		int x;

		for (x = this->_tail.size() - 1; x >= 0; x--) {
			auto tailPos = this->_tail.at(x)->getPosition();

			tailPos.y += (speed * delta);
			if (tailPos.y > 320 - (this->_tail.at(x)->getBoundingBox().size.width / 2))
				tailPos.y =  0- this->_tail.at(x)->getBoundingBox().size.width / 2;

			this->_tail.at(x)->setPosition(tailPos);
		}
	}


	SnakeSprite->setPosition(pos);
	
	break;
	}
	case 4:
	{	pos.y -= speed * delta;
	if (pos.y < 0 - (SnakeSprite->getBoundingBox().size.width / 2))
		pos.y = this->getBoundingBox().getMaxY() + SnakeSprite->getBoundingBox().size.width / 2;

	if (this->_tail.size()>0) {
		int x;

		for (x = this->_tail.size() - 1; x >= 0; x--) {
			auto tailPos = this->_tail.at(x)->getPosition();
			if (tailPos.y <0 + (this->_tail.at(x)->getBoundingBox().size.width / 2))
				tailPos.y = this->getBoundingBox().getMaxX() + this->_tail.at(x)->getBoundingBox().size.width / 2;

			tailPos.y -= (speed * delta);

			this->_tail.at(x)->setPosition(tailPos);
		}
	}

	SnakeSprite->setPosition(pos);
	break;
	}
	}

	if (foodNum != 0) {
		if (food.getRect().intersectsRect(snakeRec)) {
			this->removeChildByTag(0);
			foodNum = 0;
			int i;
			tailLength++;
			auto tail = Sprite::create("spr_Snake.png");
			
			this->_tail.pushBack(tail);
			this->addChild(tail);

			for (i = this->_tail.size() - 1; i >= 0; i--) {

				if (i == 0)
				{
					switch (dir) {
					case 1: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x + 40, SnakeSprite->getPosition().y)); break;
					case 2: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x - 40, SnakeSprite->getPosition().y)); break;
					case 3: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x, SnakeSprite->getPosition().y+40)); break;
					case 4: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x, SnakeSprite->getPosition().y-40)); break;
					}
						
					CCLOG("%d", i);
				}
				else
				{
					switch (dir) {
					case 1: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x + ((i) *40), SnakeSprite->getPosition().y)); break;
					case 2: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x - ((i)* 40), SnakeSprite->getPosition().y)); break;
					case 3: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x, SnakeSprite->getPosition().y + ((i)* 40))); break;
					case 4: this->_tail.at(i)->setPosition(Point(SnakeSprite->getPosition().x, SnakeSprite->getPosition().y - ((i)* 40))); break;
					}	CCLOG("%d", i);
				}
			}
			
			CCLOG("hit");
			//CCLOG("%d", this->_tail.size());
		}
	}
}

void SnakeGameScene::SpawnFood(float delta) {
	if (foodNum == 0) {
		food.spawnFood(this);
		
		foodNum = 1;
	}
}


void SnakeGameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
