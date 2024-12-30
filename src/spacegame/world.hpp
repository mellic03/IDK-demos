#pragma once

#include <vector>
#include "actor.hpp"

#include <IDKGameEngine/IDKGameEngine.hpp>

namespace sp
{
    class World;
}


class sp::World
{
private:
    std::vector<Actor*> m_actors;
    idk::EngineAPI &m_api;

public:
    World( idk::EngineAPI &api )
    :   m_api(api)
    {

    }

    ~World()
    {
        for (Actor *A: m_actors)
        {
            delete A;
        }
    }

    void update();

    template <typename actor_type, typename... Args>
    actor_type *createActor( Args&&... args )
    {
        auto *obj = new actor_type(m_api, *this, std::forward<Args>(args)...);
        m_actors.push_back(dynamic_cast<sp::Actor*>(obj));
        return obj;
    }
};

