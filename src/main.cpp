#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/CCAnimatedSprite.hpp>
#include <Geode/modify/ShardsPage.hpp>
#include <Geode/modify/ItemInfoPopup.hpp>
#include <Geode/modify/CommunityCreditsPage.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include <Geode/modify/PurchaseItemPopup.hpp>
#include <Geode/modify/GJGarageLayer.hpp>

using namespace geode::prelude;

//im too lazy to replace that shit X) -user95401
template <class InpT = CCNode*, class T = std::remove_pointer_t<InpT>>
T* getChildOfType(CCNode* node, int index) {
	return node->getChildByType<T*>(index);
}

class $modify (CCAnimatedSprite)
{
	virtual void animationFinished(char const* p0)
	{
		CCAnimatedSprite::animationFinished(p0);

		if (getUserObject("reset-animation-on-finish"_spr))
			runAnimation("idle01");
	}
};

class $modify (AnimatedProfilePage, ProfilePage)
{
	void onAnimate(CCObject* sender)
	{
		if (auto robotSpr = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_robotSprite)
		{
			robotSpr->runAnimation("idle02");
		}

		if (auto spiderSpr = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_spiderSprite)
		{
			spiderSpr->runAnimation("idle02");
		}
	}

	void loadPageFromUserInfo(GJUserScore* p0)
	{
		ProfilePage::loadPageFromUserInfo(p0);

		if (auto playerMenu = this->getChildByIDRecursive("player-menu"))
		{
			auto robot = playerMenu->getChildByID("player-robot");
			auto spider = playerMenu->getChildByID("player-spider");

			if (!Loader::get()->getLoadedMod("rynat.better_unlock_info"))
			{
				robot->removeFromParentAndCleanup(false);

				auto robotBtn = CCMenuItemSpriteExtra::create(robot, this, menu_selector(AnimatedProfilePage::onAnimate));
				robotBtn->setID(robot->getID());
				m_buttons->addObject(robotBtn);

				playerMenu->insertBefore(robotBtn, spider);

				spider->removeFromParentAndCleanup(false);

				auto spiderBtn = CCMenuItemSpriteExtra::create(spider, this, menu_selector(AnimatedProfilePage::onAnimate));
				spiderBtn->setID(spider->getID());
				m_buttons->addObject(spiderBtn);

				playerMenu->insertAfter(spiderBtn, robotBtn);

				playerMenu->updateLayout();
			}

			if (auto robotSpr = getChildOfType<SimplePlayer>(robot, 0)->m_robotSprite)
			{
				robotSpr->runAnimation("idle01");
				robotSpr->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
			}

			if (auto spiderSpr = getChildOfType<SimplePlayer>(spider, 0)->m_spiderSprite)
			{
				spiderSpr->runAnimation("idle01");
				spiderSpr->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
			}
		}
	}
};

class $modify (AnimatedCommentCell, CommentCell)
{
	void onAnimate(CCObject* sender)
	{
		if (auto robot = as<SimplePlayer*>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage())->m_robotSprite)
		{
			robot->runAnimation("idle02");
		}

		if (auto spider = as<SimplePlayer*>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage())->m_spiderSprite)
		{
			spider->runAnimation("idle02");
		}
	}

	void loadFromComment(GJComment* p0)
	{
		CommentCell::loadFromComment(p0);

		if (auto layer = m_mainLayer)
		{
			if (auto icon = getChildOfType<SimplePlayer>(layer, 0))
			{
				if (auto robot = icon->m_robotSprite)
				{
					robot->runAnimation("idle01");
					robot->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
				}

				if (auto spider = icon->m_spiderSprite)
				{
					spider->runAnimation("idle01");
					spider->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
				}

				if (icon->m_robotSprite || icon->m_spiderSprite)
				{
					auto menu = CCMenu::create();
					menu->setID(icon->getID());
					menu->setPosition(ccp(0, 0));

					auto pos = icon->getPosition();

					auto btn = CCMenuItemSpriteExtra::create(icon, this, menu_selector(AnimatedCommentCell::onAnimate));
					btn->setPosition(pos);
					btn->setContentSize(ccp(15, 15));

					icon->setPosition(btn->getContentSize() / 2);

					menu->addChild(btn);
					layer->insertAfter(menu, icon);
					layer->removeChild(icon, false);
				}
			}
		}		
	}
};

class $modify (ShardsPage)
{
	virtual bool init()
	{
		if (!ShardsPage::init())
			return false;

		if (auto menu = getChildOfType<CCMenu>(m_mainLayer, 0))
		{
			for (auto btn : CCArrayExt<CCMenuItemSpriteExtra*>(menu->getChildren()))
			{
				if (auto unlock = getChildOfType<GJItemIcon>(btn, 0))
				{
					if (auto player = getChildOfType<SimplePlayer>(unlock, 0))
					{
						if (player->m_robotSprite)
							player->m_robotSprite->runAnimation("idle01");

						if (player->m_spiderSprite)
							player->m_spiderSprite->runAnimation("idle01");
					}
				}
			}
		}

		return true;
	}
};

class $modify (AnimatedItemInfoPopup, ItemInfoPopup)
{
	//bui compatibility
	static void onModify(auto& self)
    {
        (void) self.setHookPriority("ItemInfoPopup::init", -1010);
    }

	void onAnimate(CCObject* sender)
	{
		if (auto robot = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_robotSprite)
		{
			robot->runAnimation("idle02");
		}

		if (auto spider = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_spiderSprite)
		{
			spider->runAnimation("idle02");
		}
	}

	bool init(int p0, UnlockType p1)
	{
		if (!ItemInfoPopup::init(p0, p1))
			return false;

		if (p1 == UnlockType::Robot || p1 == UnlockType::Spider)
		{
			if (auto unlock = getChildOfType<GJItemIcon>(m_mainLayer, 0))
			{
				if (auto icon = getChildOfType<SimplePlayer>(unlock, 0))
				{
					if (auto robot = icon->m_robotSprite)
					{
						robot->runAnimation("idle01");
						robot->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
					}

					if (auto spider = icon->m_spiderSprite)
					{
						spider->runAnimation("idle01");
						spider->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
					}
				}

				auto pos = unlock->getPosition();

				auto btn = CCMenuItemSpriteExtra::create(unlock, this, menu_selector(AnimatedItemInfoPopup::onAnimate));

				auto menu = getChildOfType<CCMenu>(m_mainLayer, 0);
				btn->setPosition(pos - menu->getPosition());

				menu->addChild(btn);
				m_mainLayer->removeChild(unlock, false);
			}
		}

		return true;
	}
};

class $modify (AnimatedCommunityCreditsPage, CommunityCreditsPage)
{
	void onAnimate(CCObject* sender)
	{
		if (auto robot = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_robotSprite)
		{
			robot->runAnimation("idle02");
		}

		if (auto spider = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_spiderSprite)
		{
			spider->runAnimation("idle02");
		}
	}

	virtual bool init()
	{
		if (!CommunityCreditsPage::init())
			return false;

		for (auto child : CCArrayExt<CCNode*>(m_mainLayer->getChildren()))
		{
			if (auto unlock = typeinfo_cast<GJItemIcon*>(child))
			{
				if (auto icon = getChildOfType<SimplePlayer>(unlock, 0))
				{					
					if (auto robot = icon->m_robotSprite)
					{
						robot->runAnimation("idle01");
						robot->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
					}

					if (auto spider = icon->m_spiderSprite)
					{
						spider->runAnimation("idle01");
						spider->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
					}
				}
			}
		}

		return true;
	}
};

class $modify (GJShopLayer)
{
	bool init(ShopType p0)
	{
		if (!GJShopLayer::init(p0))
			return false;

		if (auto bar = getChildOfType<ListButtonBar>(this, 0))
		{
			if (auto boom = getChildOfType<BoomScrollLayer>(bar, 0))
			{
				if (auto ext = getChildOfType<ExtendedLayer>(boom, 0))
				{
					for (auto page : CCArrayExt<ListButtonPage*>(ext->getChildren()))
					{
						if (auto menu = getChildOfType<CCMenu>(page, 0))
						{
							for (auto btn : CCArrayExt<CCMenuItemSpriteExtra*>(menu->getChildren()))
							{
								if (auto unlock = as<GJItemIcon*>(btn->getNormalImage()))
								{
									if (auto icon = getChildOfType<SimplePlayer>(unlock, 0))
									{
										if (icon->m_robotSprite)
											icon->m_robotSprite->runAnimation("idle01");

										if (icon->m_spiderSprite)
											icon->m_spiderSprite->runAnimation("idle01");
									}
								}
							}
						}
					}
				}
			}
		}

		return true;
	}
};

class $modify (AnimatedPurchaseItemPopup, PurchaseItemPopup)
{
	void onAnimate(CCObject* sender)
	{
		if (auto robot = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_robotSprite)
		{
			robot->runAnimation("idle02");
		}

		if (auto spider = getChildOfType<SimplePlayer>(as<CCMenuItemSpriteExtra*>(sender)->getNormalImage(), 0)->m_spiderSprite)
		{
			spider->runAnimation("idle02");
		}
	}

	bool init(GJStoreItem* p0)
	{
		if (!PurchaseItemPopup::init(p0))
			return false;

		if (auto unlock = getChildOfType<GJItemIcon>(m_mainLayer, 0))
		{
			if (auto icon = getChildOfType<SimplePlayer>(unlock, 0))
			{			
				if (!(icon->m_robotSprite || icon->m_spiderSprite))
					return true;
				
				if (auto robot = icon->m_robotSprite)
				{
					robot->runAnimation("idle01");
					robot->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
				}

				if (auto spider = icon->m_spiderSprite)
				{
					spider->runAnimation("idle01");
					spider->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
				}

				auto pos = unlock->getPosition();

				auto menu = getChildOfType<CCMenu>(m_mainLayer, 0);

				auto btn = CCMenuItemSpriteExtra::create(unlock, this, menu_selector(AnimatedPurchaseItemPopup::onAnimate));
				btn->setPosition(pos - menu->getPosition());

				menu->addChild(btn);
				m_mainLayer->insertBefore(menu, unlock);
				m_mainLayer->removeChild(unlock, false);
			}
		}

		return true;
	}
};

class $modify (GJGarageLayer)
{
	virtual bool init()
	{
		if (!GJGarageLayer::init())
			return false;

		if (auto icon = getChildOfType<SimplePlayer>(this, 0))
		{
			if (auto robot = icon->m_robotSprite)
			{
				robot->runAnimation("idle01");
				robot->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
			}

			if (auto spider = icon->m_spiderSprite)
			{
				spider->runAnimation("idle01");
				spider->setUserObject("reset-animation-on-finish"_spr, CCNode::create());
			}
		}

		return true;
	}

	void setupPage(int p0, IconType p1)
	{
		GJGarageLayer::setupPage(p0, p1);

		if (p1 == IconType::Robot || p1 == IconType::Spider)
		{
			if (auto bar = getChildOfType<ListButtonBar>(this, 0))
			{
				if (auto boom = getChildOfType<BoomScrollLayer>(bar, 0))
				{
					if (auto ext = getChildOfType<ExtendedLayer>(boom, 0))
					{
						for (auto page : CCArrayExt<ListButtonPage*>(ext->getChildren()))
						{
							if (auto menu = getChildOfType<CCMenu>(page, 0))
							{
								for (auto btn : CCArrayExt<CCMenuItemSpriteExtra*>(menu->getChildren()))
								{
									if (auto unlock = as<GJItemIcon*>(btn->getNormalImage()))
									{
										if (auto icon = getChildOfType<SimplePlayer>(unlock, 0))
										{
											if (icon->m_robotSprite)
												icon->m_robotSprite->runAnimation("idle01");

											if (icon->m_spiderSprite)
												icon->m_spiderSprite->runAnimation("idle01");
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
};