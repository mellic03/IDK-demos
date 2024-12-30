#pragma once

#include <vector>
#include "actor.hpp"

namespace sp
{
    class World;
}


class sp::World
{
private:
    std::vector<Actor*> m_actors;

public:
    void update();

    template <typename actor_type, typename... Args>
    actor_type *createActor( Args&&... args )
    {
        auto *obj = new actor_type(*this, std::forward<Args>(args)...);
        m_actors.push_back(dynamic_cast<sp::Actor*>(obj));
        return obj;
    }
};

