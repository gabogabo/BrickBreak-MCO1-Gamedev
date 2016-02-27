#include "Brick.h"

USING_NS_CC;

Brick::Brick() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
}

void Brick::spawnBrick(cocos2d::Layer *layer, int z, int x, int yOffset) {
	
	switch (z) {
	case 3: {BrickSprite = Sprite::create("spr_Metal.png"); brickLife = 3; BrickSprite->setTag(5); } break;
	case 2: {BrickSprite = Sprite::create("spr_Rock.png"); brickLife = 2; BrickSprite->setTag(4);
	} break;
	case 1: {BrickSprite = Sprite::create("spr_Brick.png"); brickLife = 1; BrickSprite->setTag(3); } break;
	}
	auto brickBody = PhysicsBody::createBox(BrickSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	brickBody->getShape(0)->setRestitution(1.0f);
	brickBody->getShape(0)->setFriction(0.0f);
	brickBody->getShape(0)->setDensity(10.0f);
	brickBody->setContactTestBitmask(0x000001);
	brickBody->setDynamic(false);

	int xOffset = 15+  BrickSprite->getContentSize().width / 2 + ((BrickSprite->getContentSize().width +15)*x);
	BrickSprite->setPosition(xOffset, yOffset);

	BrickSprite->setPhysicsBody(brickBody);




	layer->addChild(BrickSprite, 100);



}



cocos2d::Vec2 Brick::getSpritePosition() {
	return BrickSprite->getPosition();
}
float Brick::getSpritePositionY() {
	return BrickSprite->getPositionY();
}


cocos2d::Size Brick::getSpriteSize() {

	return BrickSprite->getContentSize();
}
cocos2d::Sprite* Brick::changeSprite() {
	return BrickSprite;
}

int Brick::getBrickLife() {
	return brickLife;
}
void Brick::setBrickLife(int xLife) {
	this->brickLife = xLife;
}
void Brick::setSpritePosition(float x, float y) {
	BrickSprite->setPosition(x,y);
}
void Brick::setSpriteVelocity() {
	BrickSprite->getPhysicsBody()->setVelocity(Vect(0.0f,0.0f));
}