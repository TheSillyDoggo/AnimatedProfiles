#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/CCAnimatedSprite.hpp>

using namespace geode::prelude;

class $modify(ProfilePage) {
	bool init(int p0, bool p1)
	{
		if (!ProfilePage::init(p0, p1))
			return false;

		if (m_score == nullptr)
			return true;

		as<SimplePlayer*>(as<CCNode*>(this->getChildren()->objectAtIndex(0))->getChildByID("player-menu")->getChildByID("player-robot")->getChildByID("player-robot"))->m_robotSprite->runAnimation("idle01"); // idle 01 and idle 02

		as<SimplePlayer*>(as<CCNode*>(this->getChildren()->objectAtIndex(0))->getChildByID("player-menu")->getChildByID("player-spider")->getChildByID("player-spider"))->m_spiderSprite->runAnimation("idle01"); // idle 01 and idle 02

		return true;
	}

	TodoReturn loadPageFromUserInfo(GJUserScore* p0)
	{
		ProfilePage::loadPageFromUserInfo(p0);

		as<SimplePlayer*>(as<CCNode*>(this->getChildren()->objectAtIndex(0))->getChildByID("player-menu")->getChildByID("player-robot")->getChildByID("player-robot"))->m_robotSprite->runAnimation("idle01"); // idle 01 and idle 02

		as<SimplePlayer*>(as<CCNode*>(this->getChildren()->objectAtIndex(0))->getChildByID("player-menu")->getChildByID("player-spider")->getChildByID("player-spider"))->m_spiderSprite->runAnimation("idle01"); // idle 01 and idle 02
	}
};

class $modify (CommentCell)
{
	void loadFromComment(GJComment* p0)
	{
		CommentCell::loadFromComment(p0);

		auto l = as<CCLayer*>(this->getChildren()->objectAtIndex(1));

		auto sp = getChildOfType<SimplePlayer>(l, 0);

		if (!sp)
			return;

		sp->setID("player-icon");

		if (sp->m_robotSprite)
			sp->m_robotSprite->runAnimation("idle01");

		if (sp->m_spiderSprite)
			sp->m_spiderSprite->runAnimation("idle01");
	}
};

class $modify (CCAnimatedSprite)
{
    TodoReturn runAnimation(gd::string p0)
	{
		log::info("Playing animation: {}", p0);
		CCAnimatedSprite::runAnimation(p0);
	}
};