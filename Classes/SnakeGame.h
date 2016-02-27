#ifndef __SNAKE_GAME_SCENE_H__
#define __SNAKE_GAME_SCENE_H__

#include "cocos2d.h"
#include "Snake.h"
#include "Food.h"

class SnakeGameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SnakeGameScene);
	
	void update(float) override;
	void SpawnFood(float);
private:
	cocos2d::Sprite *SnakeSprite;
	cocos2d::Sprite *FoodSprite;
	cocos2d::Sprite *SpeedUpSprite;
	cocos2d::Sprite *Times2Sprite;
	cocos2d::Sprite *SpawnPartySprite;

	cocos2d::EventKeyboard::KeyCode direction;
	cocos2d::Vec2 pos;
	cocos2d::Vector<cocos2d::Sprite*> _tail;



	int tailLength;
	int speed;
	int dir;
	int pDir;
	int foodNum;
	//Snake *snake;
	Food food;
};

#endif // __SNAKE_GAME_SCENE_H__
