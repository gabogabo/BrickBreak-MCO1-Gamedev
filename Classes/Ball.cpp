#include "Ball.h"

USING_NS_CC;

Ball::Ball(cocos2d::Layer *layer) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BallSprite = Sprite::create("spr_BBall.png");
	BallSprite->setPosition(Point((visibleSize.width / 2) + origin.x, 41 + origin.y));
	launched = false;

	auto ballBody = PhysicsBody::createCircle(BallSprite->getContentSize().width / 2);
	//BallSprite->setPhysicsBody(ballBody);
	layer->addChild(BallSprite, 100);
	
	
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setDensity(1.0f);
	ballBody->setGravityEnable(false);

	//force = Vect(00000.0f, 00000.0f);
	//ballBody->applyImpulse(force);
	BallSprite->setPhysicsBody(ballBody);
	ballBody->setCollisionBitmask(0x000001);
	ballBody->setContactTestBitmask(true);
	BallSprite->setTag(1);

}

void Ball::setSpritePosition(cocos2d::Vec2 pos) {
	BallSprite->setPosition(pos);
}

cocos2d::Vec2 Ball::getSpritePosition() {
	return BallSprite->getPosition();
}
float Ball::getSpritePositionY() {
	return BallSprite->getPositionY();
}


bool Ball::isLaunched() {
	return launched;
}

void Ball::setIsLaunched(bool launch) {
	this->launched = launch;
}
void Ball::setForce(float x, float y) {
	force = Vect(x, y);
	BallSprite->getPhysicsBody()->applyImpulse(force);


}
void Ball::setSpriteVelocity() {
	BallSprite->getPhysicsBody()->setVelocity(Vect(0.0f,0.0f));
}