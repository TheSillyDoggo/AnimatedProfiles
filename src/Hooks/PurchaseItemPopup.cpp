#include <Geode/Geode.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedPurchasePopup, PurchaseItemPopup)
{
    void onAnimate(CCObject* sender)
    {
        Utils::animateJump(static_cast<CCMenuItemSprite*>(sender)->getNormalImage()->getChildByType<SimplePlayer>(0));
    }

    bool init(GJStoreItem* item)
    {
        if (!PurchaseItemPopup::init(item))
            return false;

        if (auto sp = m_mainLayer->getChildByID("icon")->getChildByType<SimplePlayer>(0))
        {
            if (!(sp->m_robotSprite || sp->m_spiderSprite))
                return true;

            Utils::animate(sp);

            auto menu = CCMenu::create();
            menu->setPosition(sp->getParent()->getPosition());
            menu->setID("proxy-menu"_spr);
            
            auto btn = ProxyButton::create(sp->getParent(), this, menu_selector(AnimatedPurchasePopup::onAnimate));
            menu->addChild(btn);

            m_mainLayer->addChild(menu);
        }

        return true;
    }
};