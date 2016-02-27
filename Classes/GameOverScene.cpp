#include "GameOverScene.h"
#include "BrickBreak.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto gameOver = Sprite::create("spr_GameOver.png");
	gameOver->setPosition(visibleSize.width / 2 , (visibleSize.height / 2)+90);
	this->addChild(gameOver);

	auto retry = Sprite::create("spr_Retry.png");
	retry->setPosition(visibleSize.width / 2, (visibleSize.height / 2) );
	this->addChild(retry);

	auto yes = MenuItemImage::create("spr_yes.png","spr_yesOnHover.png",CC_CALLBACK_1(GameOverScene::GoToBrickBreak,this));
	yes->setPosition(visibleSize.width / 2, (visibleSize.height / 2) - 50 );
	//->addChild(yes);

	auto no = MenuItemImage::create("spr_no.png", "spr_noOnHover.png", CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
	no->setPosition(visibleSize.width / 2, (visibleSize.height / 2) -80);
	//this->addChild(no);

	auto menu = Menu::create(yes,no,nullptr);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

    /////////////////////////////
	return true;


}


void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender) {

}
void GameOverScene::GoToBrickBreak(cocos2d::Ref *sender) {
	auto scene = BrickBreak::createScene();
	Director::getInstance( )->replaceScene(TransitionFade::create(1.0f,scene));
}

void GameOverScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
