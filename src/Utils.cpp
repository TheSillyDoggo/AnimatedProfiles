#include "Utils.hpp"
#include <Geode/modify/CCAnimatedSprite.hpp>

void handle(CCAnimatedSprite* animated, std::string anim)
{
    if (!animated)
        return;
    
    animated->setUserFlag("reset-animation-on-finish"_spr, true);
    animated->runAnimation(anim);
}

void Utils::animate(SimplePlayer* player)
{
    handle(player->m_robotSprite, "idle01");
    handle(player->m_spiderSprite, "idle01");
}

void Utils::animateJump(SimplePlayer* player)
{
    handle(player->m_robotSprite, "idle02");
    handle(player->m_spiderSprite, "idle02");
}

class $modify (CCAnimatedSprite)
{
	virtual void animationFinished(char const* p0)
	{
		CCAnimatedSprite::animationFinished(p0);

		if (getUserFlag("reset-animation-on-finish"_spr))
			runAnimation("idle01");
	}
};