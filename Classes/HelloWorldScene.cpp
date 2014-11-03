#include "HelloWorldScene.h"
#include "Net/MWebSocket.h"
#include "Net/command/CommonCommand.h"
#include "Scene/UI_Login.h"
#include "Net/command/SendNetWork.h"
#include "Net/request/RequestTest.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));


    
    label = LabelTTF::create("Hello World", "Arial", 24);
    
    labelShow = LabelTTF::create("the websocket is not connecting.", "Arial", 24);
    labelShow->setPosition(Vec2(200, 100));
    this->addChild(labelShow);
    
    auto sendLabel = MenuItemFont::create("Send Text", CC_CALLBACK_0(HelloWorld::send, this));
    sendLabel->setPosition(Vec2(300, 400));
    
    auto connetLavbel = MenuItemFont::create("Connet", [](Ref* ref){
        CommonCommand::getInstance()->creatConnection();
    });
    connetLavbel->setPosition(Vec2(500, 400));
    
    auto menu = Menu::create(closeItem, sendLabel, connetLavbel,NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    this->scheduleUpdate();
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

//    auto sprite = Sprite::create("HelloWorld.png");
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    this->addChild(sprite, 0);
    
    // 测试游戏会不会因为webSocket而阻塞
    auto test = Sprite::create("CloseNormal.png");
    this->addChild(test);
    test->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    test->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.0f, Point(100,0)),MoveBy::create(1.0f, Point(-100,0)), NULL)));
    
    
    return true;
}

void HelloWorld::update(float dt)
{
    if(CommonCommand::getInstance()->isConnected())
    {
        labelShow->setString("The webSocket is connected~");
    }else
    {
        labelShow->setString("The webSocket is not connect.");
    }
}

void HelloWorld::send()
{
//    _socket->send();
    auto mess = new HMessage();
//
    mess->putInt(10);
    mess->putShort(20);
    mess->putLong(12);
    mess->putUTF8("fuck~~~~~~");
//     发送消息
    CommonCommand::getInstance()->sendMessage(mess);
//    SendNetWork::getInstance()->AddNetCommand(new RequestTest());
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
//    Director::getInstance()->replaceScene(UI_Login::scene());
}
