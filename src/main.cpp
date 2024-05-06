#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/CCAnimatedSprite.hpp>

using namespace geode::prelude;

class $modify(ProfilePage) {
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("ProfilePage::loadPageFromUserInfo", INT64_MIN + 1);
	}
	void loadPageFromUserInfo(GJUserScore* p0) {
		ProfilePage::loadPageFromUserInfo(p0);
		if (!Loader::get()->isModLoaded("rynat.better_unlock_info")) {
			if (auto l = getChildByIDRecursive("player-menu"))
			{
				if (auto r = l->getChildByID("player-robot"))
				{
					if (auto robot = typeinfo_cast<SimplePlayer*>(r->getChildByID("player-robot"))->m_robotSprite) {
						robot->runAnimation("idle01");
					}
				}
				if (auto s = l->getChildByID("player-spider"))
				{
					if (auto spider = typeinfo_cast<SimplePlayer*>(s->getChildByID("player-spider"))->m_spiderSprite) {
						spider->runAnimation("idle01");
					}
				}
			}
		}
	}
};

class $modify(CommentCell) {
	static void onModify(auto & self)
	{
		(void) self.setHookPriority("CommentCell::loadFromComment", INT64_MIN + 1);
	}
	void loadFromComment(GJComment* p0) {
		CommentCell::loadFromComment(p0);
		if (auto l = getChildOfType<CCLayer>(this, 1)) {
			if (auto sp = getChildOfType<SimplePlayer>(l, 0)) {
				if (sp->m_robotSprite) {
					sp->m_robotSprite->runAnimation("idle01");
				}
				if (sp->m_spiderSprite) {
					sp->m_spiderSprite->runAnimation("idle01");
				}
			}
		}
	}
};