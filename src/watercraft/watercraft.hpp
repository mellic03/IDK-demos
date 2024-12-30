#pragma once

#include <IDKGameEngine/idk_engine_api.hpp>
#include <demo-common/actor.hpp>


namespace demo
{
    class WaterCraft;
}


class demo::WaterCraft: public idk::Actor
{
private:
    int m_body;
    int m_seat;
    glm::vec3 m_vel;

public:
    WaterCraft( const glm::vec3 &pos = glm::vec3(0.0f) );

    virtual void update( idk::EngineAPI& ) override;

    int getBody() { return m_body; }
    int getSeat() { return m_seat; }

    void addVel( const glm::vec3 &v ) { m_vel += v; }

};


