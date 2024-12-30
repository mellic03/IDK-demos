#pragma once

#include <glm/glm.hpp>
#include <IDKGameEngine/idk_engine_api.hpp>


namespace idk
{
    class Actor;
}


class idk::Actor
{
protected:
    int m_obj;

public:
    Actor( const glm::vec3 &pos = glm::vec3(0.0f) );

    virtual void update( idk::EngineAPI& ) {  };

    const int getID() const { return m_obj; }

    virtual void move( const glm::vec3& );
    virtual void look( const glm::vec2& );

    virtual void moveTo( const glm::vec3& ) {  }
    virtual void lookTo( const glm::vec3& ) {  }

};

