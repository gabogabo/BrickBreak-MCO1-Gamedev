#ifndef __Ball_H__
#define __Ball_H__

#include "cocos2d.h"

class Ball
{
public:
	Ball(cocos2d::Layer *layer);

	void setSpritePosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 getSpritePosition();
	float getSpritePositionY();
	bool isLaunched();
	void setIsLaunched(bool launch);
	void setSpriteVelocity();
	void setForce(float x, float y);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Vect force;

	cocos2d::Sprite *BallSprite;
	bool launched;
};

#endif // __Ball_H__
