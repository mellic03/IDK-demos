#pragma once
#include <libidk/idk_glm.hpp>
#include "common.hpp"


class idk::Actor
{
private:
    friend class World;
    int m_ID;

protected:
    idk::EngineAPI &m_api;
    idk::World &m_world;
    int m_obj = -1;

public:
    Actor( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    virtual ~Actor();

    virtual void update();
    virtual void fixedUpdate( float timestep );
    virtual void render( idk::RenderEngine& );

    int   actorID()  { return m_ID;    }
    int   objID()    { return m_obj;   }
    auto &getWorld() { return m_world; }

    glm::vec3 getWorldPosition() const;
    glm::vec3 getLocalPosition() const;
    glm::vec3 getFront() const;

};


