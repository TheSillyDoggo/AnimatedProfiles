#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $modify (AnimatedGarageLayer, GJGarageLayer)
{
    virtual bool init()
    {
        if (!GJGarageLayer::init())
            return false;

        if (auto icon = typeinfo_cast<SimplePlayer*>(getChildByIDRecursive("player-icon")))
            Utils::animate(icon);

        if (auto icon = typeinfo_cast<SimplePlayer*>(getChildByIDRecursive("player2-icon")))
            Utils::animate(icon);

        return true;
    }
};