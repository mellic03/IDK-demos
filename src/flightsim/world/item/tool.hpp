#pragma once
#include <flightsim/world/world/item.hpp>
#include <libidk/idk_string.hpp>

namespace idk
{
    class Tool;
}


class idk::Tool: public idk::Item
{
protected:

public:
    glm::vec3 sway_pos = glm::vec3(0.0);
    glm::vec3 curr_pos;
    glm::vec3 curr_rot;

    Tool( idk::EngineAPI&, World& );
    virtual bool use() = 0;
};

