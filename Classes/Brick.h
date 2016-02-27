#ifndef __Brick_H__
#define __Brick_H__

#include "cocos2d.h"

class Brick
{
public:
	Brick();

	
	cocos2d::Vec2 getSpritePosition();
	float getSpritePositionY();
	
	void setBrickLife(int xLife);
	void setSpriteVelocity();
	void setSpritePosition(float x, float y);
	void spawnBrick(cocos2d::Layer *layer, int z,int x, int yOffset);
	cocos2d::Size getSpriteSize();
	cocos2d::Sprite* changeSprite();

	int getBrickLife();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Vect force;

	cocos2d::Sprite *BrickSprite;

	int brickLife;
	bool launched;
};

#endif // __Brick_H__
