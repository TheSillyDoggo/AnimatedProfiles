#include <Geode/Geode.hpp>
#include <Geode/modify/CharacterColorPage.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedColorPage, CharacterColorPage)
{
    virtual bool init()
    {
        if (!CharacterColorPage::init())
            return false;

        if (auto icon = typeinfo_cast<SimplePlayer*>(m_mainLayer->getChildByID("robot-icon")))
            Utils::animate(icon);

        if (auto icon = typeinfo_cast<SimplePlayer*>(m_mainLayer->getChildByID("spider-icon")))
            Utils::animate(icon);

        return true;
    }
};