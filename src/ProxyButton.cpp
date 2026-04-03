#include "ProxyButton.hpp"

using namespace geode::prelude;

ProxyButton* ProxyButton::create(CCNode* sprite, CCObject* target, SEL_MenuHandler callback)
{
    auto pRet = new ProxyButton();
    pRet->init(sprite, nullptr, target, callback);
    sprite->setVisible(false);
    return pRet;
}

void ProxyButton::visit()
{
    m_pNormalImage->setVisible(true);

    CCNode::visit();

    m_pNormalImage->setVisible(false);
}