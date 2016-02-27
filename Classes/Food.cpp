#include "Food.h"

USING_NS_CC;

Food::Food() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	
}

void Food::spawnFood(cocos2d::Layer *layer) {
	CCLOG("YAY FOOD");

	//auto food = Sprite::create("spr_Food.png");
	//bBox = food->getBoundingBox();
	FoodSprite = Sprite::create("spr_Food.png");
	bBox = FoodSprite->getBoundingBox();

	randomX = CCRANDOM_0_1() * 480;

	randomY = CCRANDOM_0_1() * 320;

	CCLOG("%f",randomX);
	if (randomX < 40)
		randomX = 40;
	if (randomX > 440)
		randomX = 440;
	CCLOG("%f",randomY);
	if (randomY < 40)
		randomY = 40;
	if (randomY > 280)
		randomY = 280;

	FoodSprite->setPosition(Point((visibleSize.width/2) + randomX, (visibleSize.height/2)+ randomY));
	FoodSprite->setTag(0);
	layer->addChild(FoodSprite);
}

Rect Food::getRect() {
	return FoodSprite->getBoundingBox();
}

float Food::getRandomX() {
	return randomX;
}

float Food::getRandomY() {
	return randomY;
}