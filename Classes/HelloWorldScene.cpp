/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CT_Player.h"
#include <CT_PlayerState.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    setupUI();

    myPlayer = std::make_shared<CT_Player>();
    myPlayer->init(myPlayer);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    myPlayer->skeleton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    addChild(myPlayer->skeleton);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    scheduleUpdate();
    return true;
}

void HelloWorld::setupUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // add a stop button
    auto stopItem = MenuItemImage::create(
        "button.png",
        "button.png",
        CC_CALLBACK_1(HelloWorld::menuStopCallback, this));

    if (stopItem == nullptr ||
        stopItem->getContentSize().width <= 0 ||
        stopItem->getContentSize().height <= 0)
    {
        problemLoading("'button.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - stopItem->getContentSize().width / 2;
        float y = origin.y + stopItem->getContentSize().height;
        stopItem->setPosition(Vec2(x, y));
        auto label = Label::createWithTTF("Stop", "fonts/Marker Felt.ttf", 64, stopItem->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
        stopItem->addChild(label, 1);
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2::ZERO);
    }

    // add an attack button
    auto attackItem = MenuItemImage::create(
        "button.png",
        "button.png",
        CC_CALLBACK_1(HelloWorld::menuAttackCallback, this));

    if (attackItem == nullptr ||
        attackItem->getContentSize().width <= 0 ||
        attackItem->getContentSize().height <= 0)
    {
        problemLoading("'button.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - attackItem->getContentSize().width / 2;
        float y = origin.y + attackItem->getContentSize().height * 2;
        attackItem->setPosition(Vec2(x, y));
        auto label = Label::createWithTTF("Attack", "fonts/Marker Felt.ttf", 64, attackItem->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
        attackItem->addChild(label, 1);
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(Vec2::ZERO);
    }
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, stopItem, attackItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
}

void HelloWorld::update(float deltaTime)
{
    myPlayer->FSM->Update(deltaTime);
}

bool HelloWorld::onTouchesBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    myPlayer->destination = touch->getLocation();
    myPlayer->destinationChanged = true;
    myPlayer->stopPressed = false;
    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void HelloWorld::menuStopCallback(cocos2d::Ref* pSender)
{
    myPlayer->stopPressed = true;
}

void HelloWorld::menuAttackCallback(cocos2d::Ref* pSender)
{
    myPlayer->attackPressed = true;
}
