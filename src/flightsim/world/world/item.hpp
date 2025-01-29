#pragma once
#include "common.hpp"
#include <libidk/idk_glm.hpp>


class idk::Item
{
private:
    friend class World;
    int m_ID;

protected:
    idk::EngineAPI &m_api;
    idk::World &m_world;
    int m_obj;
    
    friend class Character;
    Character *m_owner;

public:
     Item( idk::EngineAPI&, World&, const glm::vec3 &p = glm::vec3(0.0f) );
    //  Item( idk::EngineAPI&, World&, Character *owner = nullptr );
     virtual ~Item();

    int        itemID()   { return m_ID;    }
    int        objID()    { return m_obj;   }

    virtual void update() = 0;
    virtual void render( idk::RenderEngine& ) = 0;
    virtual void setOwner( Character *C ) { m_owner = C; }
    Character   *getOwner() { return m_owner; }
    auto        &getWorld() { return m_world; }

};

