#pragma once

#include <libidk/idk_glm.hpp>


namespace idk
{
    class EngineAPI;
    struct RenderNode;
}

namespace sp
{
    class Actor;
    class ActorVisible;
    class World;
}


class sp::Actor
{
protected:
    idk::EngineAPI &m_api;
    sp::World &m_world;
    int m_obj;

private:

public:
    Actor( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );

    virtual void update() {  };
};


class sp::ActorVisible: public sp::Actor
{
private:

public:
    ActorVisible( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    virtual void update() override;

};



