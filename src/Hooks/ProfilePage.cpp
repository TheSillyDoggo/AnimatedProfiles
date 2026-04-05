#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedProfilePage, ProfilePage)
{
	void onAnimate(CCObject* sender)
	{
        Utils::animateJump(static_cast<CCMenuItemSprite*>(sender)->getNormalImage()->getChildByType<SimplePlayer>(0));
	}

    static void onModify(auto& self)
    {
        (void)self.setHookPriority("ProfilePage::loadPageFromUserInfo", Priority::First);
    }

	void loadPageFromUserInfo(GJUserScore* p0)
	{
		ProfilePage::loadPageFromUserInfo(p0);

		if (auto playerMenu = m_mainLayer->getChildByID("player-menu"))
		{
            for (auto child : CCArrayExt<CCNode*>(playerMenu->getChildren()))
            {
                if (child->getID() == "player-robot" || child->getID() == "player-spider")
                {
                    auto btn = ProxyButton::create(child, this, menu_selector(AnimatedProfilePage::onAnimate));
                    btn->setID(fmt::format("{}proxy-{}", ""_spr, child->getID()));

                    Utils::animate(child->getChildByType<SimplePlayer>(0));

                    playerMenu->insertAfter(btn, playerMenu->getChildByID("player-wave"));
                }
            }

            playerMenu->sortAllChildren();
            playerMenu->updateLayout();
		}
	}
};