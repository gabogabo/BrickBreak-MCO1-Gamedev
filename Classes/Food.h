#ifndef __Food_H__
#define __Food_H__

#include "cocos2d.h"

class Food
{
public:
	Food();

	void spawnFood(cocos2d::Layer *layer);
	cocos2d::Rect getRect();

	float getRandomX();
	float getRandomY();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *FoodSprite;
	cocos2d::Rect bBox;

	float randomX;
	float randomY;
};

#endif // __Food_H__
