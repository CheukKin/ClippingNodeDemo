#ifndef __DADONGSCENE_H__
#define __DADONGSCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;


class DaDong: public cocos2d::Layer
{
public:
    virtual bool init();  
    static cocos2d::Scene* scene();
    void menuCloseCallback(Ref* sender);
	CREATE_FUNC(DaDong);

	Size visibleSize;
	Size winSize;
	Vec2 origin;

	ClippingNode* holesClipper; //裁剪节点
	Node* holesStencil;         //模板节点
	Node* holes;                //底板节点
	 
	//触摸回调
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	//添加小洞
	void pokeHoleAtPoint(Vec2 point);
};

#endif // __HELLOWORLD_SCENE_H__
