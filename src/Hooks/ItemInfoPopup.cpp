#include <Geode/Geode.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedInfoPopup, ItemInfoPopup)
{
    void onAnimate(CCObject* sender)
    {
        Utils::animateJump(static_cast<CCMenuItemSprite*>(sender)->getNormalImage()->getChildByType<SimplePlayer>(0));
    }

    bool init(int id, UnlockType type)
    {
        if (!ItemInfoPopup::init(id, type))
            return false;

        if (auto sp = m_mainLayer->getChildByID("item-icon")->getChildByType<SimplePlayer>(0))
        {
            if (!(sp->m_robotSprite || sp->m_spiderSprite))
                return true;

            Utils::animate(sp);

            auto menu = CCMenu::create();
            menu->setPosition(sp->getParent()->getPosition());
            menu->setID("proxy-menu"_spr);
            
            auto btn = ProxyButton::create(sp->getParent(), this, menu_selector(AnimatedInfoPopup::onAnimate));
            menu->addChild(btn);

            m_mainLayer->addChild(menu);
        }

        return true;
    }
};