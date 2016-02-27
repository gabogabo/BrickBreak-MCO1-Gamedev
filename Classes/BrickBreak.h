#ifndef __BRICK_BREAK_H__
#define __BRICK_BREAK_H__

#include "cocos2d.h"
#include "Ball.h"
#include "Food.h"
#include "Brick.h"
USING_NS_CC;


class BrickBreak : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BrickBreak);
	
	void update(float) override;
	void refreshPaddle(float delta);

	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode);
	bool hasCollided(PhysicsContact& collide);
	
	

	PhysicsWorld *bworld;
	void setPhyWorld(PhysicsWorld *world) { bworld = world; };
	void checkWin(float delta);
	
private:
	cocos2d::Sprite *PaddleSprite;
	cocos2d::Sprite *BrickSprite;
	cocos2d::Sprite *SpeedUpSprite;
	cocos2d::Sprite *Times2Sprite;
	cocos2d::Sprite *SpawnPartySprite;
	cocos2d::Sprite *edgeSp;


	cocos2d::EventKeyboard::KeyCode direction;
	cocos2d::Vec2 pos;
	

	static std::map<cocos2d::EventKeyboard::KeyCode,
		std::chrono::high_resolution_clock::time_point> keys;

	Ball *ball;
	Brick *brick;

	int bricksLeft;
	int playerLife;
	int tailLength;
	int speed;
	int dir;
	int pDir;
	int foodNum;
	
};

#endif // __BRICK_BREAK_H__
