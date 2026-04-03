#pragma once

#include <Geode/Geode.hpp>

class ProxyButton : public CCMenuItemSpriteExtra
{
    public:
        static ProxyButton* create(cocos2d::CCNode* sprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback);

        virtual void visit();
};