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
    glm::vec3 m_pos;

private:


public:
    glm::vec3 &pos;
    Actor( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );

    virtual void update() {  };
};


class sp::ActorVisible: public sp::Actor
{
private:
    int m_nodeid;

public:
    ActorVisible( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    virtual void update() override;

};



