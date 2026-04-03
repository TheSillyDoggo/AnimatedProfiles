#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedCommentCell, CommentCell)
{
	void onAnimate(CCObject* sender)
	{
        Utils::animateJump(static_cast<SimplePlayer*>(static_cast<CCMenuItemSprite*>(sender)->getNormalImage()));
	}

	void loadFromComment(GJComment* p0)
	{
		CommentCell::loadFromComment(p0);

		if (auto player = typeinfo_cast<SimplePlayer*>(getChildByIDRecursive("player-icon")))
		{
            if (!(player->m_robotSprite || player->m_spiderSprite))
                return;

            auto playerMenu = player->getParent();
            
            auto btn = ProxyButton::create(player, this, menu_selector(AnimatedCommentCell::onAnimate));
            btn->setID(fmt::format("{}proxy-{}", ""_spr, player->getID()));

            Utils::animate(player);

            playerMenu->addChild(btn, -1);

            playerMenu->sortAllChildren();
            playerMenu->updateLayout();
		}
	}
};