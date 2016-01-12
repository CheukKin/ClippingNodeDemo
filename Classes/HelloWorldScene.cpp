#include "HelloWorldScene.h"

USING_NS_CC;
using namespace std;



Scene* HelloWorld::scene()
{
	Scene* scene = Scene::create();
	HelloWorld* layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if (!Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
	winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();

/*
	holesClipper = ClippingNode::create();
	holesClipper->setPosition(visibleSize / 2);
//  holesClipper的孩子 作为底板
	this->addChild(holesClipper);
//  是否显示被裁剪下来的底板内容
	holesClipper->setInverted(true);
//  表示只绘制模板中alpha像素大于0.5的内容。
	holesClipper->setAlphaThreshold(0.5f);

	holesClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
//模板
	holesStencil = Node::create();
	holesClipper->setStencil(holesStencil);
	holesStencil->addChild(Sprite::create("ball.png"), -1);

	holes = Node::create();
	holesClipper->addChild(holes);

	Sprite* content = Sprite::create("blocks.png");
	holesClipper->addChild(content, -1, "content");

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    */
    //模板
    Sprite* gameTitle = Sprite::create("game_title.png");
    
    Size clipSize = gameTitle->getContentSize();
    
    Sprite* spark = Sprite::create("spark.png");
    spark->setPosition(-clipSize.width, 0);
    
    
    //创建 裁切节点
    ClippingNode* clippingNode = ClippingNode::create();
//   像素大于0的才会渲染
    clippingNode->setAlphaThreshold(0);//模板的透明部分是否描边 取值[0,1]
    clippingNode->setPosition(visibleSize / 2);
    this->addChild(clippingNode);
    CCLOG("%f,%f",clippingNode->getPosition().x,clippingNode->getPosition().y);
    CCLOG("%f,%f",spark->getPosition().x,spark->getPosition().y);
    
    
    Sprite*  helloWorld = Sprite::create("HelloWorld.png");
    
//  gameTitle为模板 模板就是要裁切的形状，就是按照模板形状做裁切的描边，模板是不显示的，只描边
    clippingNode->setStencil(gameTitle);
//    clippingNode->setInverted(true);//倒置裁切
//  gameTitle也作为底板 底板就是被裁切的，裁切内容才能显示出来 给clippingNode->addChild添加底板，底板用于显示
    clippingNode->addChild(gameTitle, 1);
    clippingNode->addChild(spark,2);
    
    
    MoveTo* moveAction = MoveTo::create(2.0f, Vec2(clipSize.width, 0));
    MoveTo* moveBackAction = MoveTo::create(2.0f, Vec2(-clipSize.width, 0));
    Sequence* seq = Sequence::create(moveAction, moveBackAction, NULL);
    RepeatForever* repeatAction = RepeatForever::create(seq);
    spark->runAction(repeatAction);

    return true;
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{

	Vec2 point = touches[0]->getLocation();
	point = holesClipper->convertToNodeSpace(point);

	Sprite* content =(Sprite*)this->holesClipper ->getChildByName("content");
	Size contentSize = content->getContentSize();
	Rect rect = Rect(-contentSize.width / 2, -contentSize.height / 2, contentSize.width, contentSize.height);

	if (rect.containsPoint(point))
	{
		pokeHoleAtPoint(point);
	}
}

void HelloWorld::pokeHoleAtPoint(Vec2 point)
{
	CCLOG("Add a Hole!!!");

	auto hole = Sprite::create("hole_effect.png");
	hole->setPosition(point);
	holes->addChild(hole);


	auto holeStencil = Sprite::create("hole_stencil.png");
	holeStencil->setPosition(point);
	holesStencil->addChild(holeStencil);

	holesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}