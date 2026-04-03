#include <Geode/Geode.hpp>
#include <alphalaneous.alphas_geode_utils/include/ObjectModify.hpp>
#include "../Utils.hpp"
#include "../ProxyButton.hpp"

using namespace geode::prelude;

class $nodeModify(GJItemIcon)
{
	void modify()
    {
        if (auto player = getChildByType<SimplePlayer>(0))
        {
            Utils::animate(player);
        }
    }
};