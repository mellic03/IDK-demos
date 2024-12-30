#include "fsim.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>


FlightSim::FlightSim()
:   m_world()
{
    m_world.config.timestep  = 1.0f / 16.0f;
    m_world.config.gravity.y = -0.81f;
}


void
FlightSim::setup( idk::EngineAPI &api )
{
    // auto *body  = m_world.createBody<fsim::RigidBody>(glm::vec3(0.0f));
    m_craft = m_world.createBody<fsim::Aircraft>(glm::vec3(0.0, 4.0, 0.0));
    m_aircraft.push_back(m_craft);
}


void
FlightSim::mainloop( idk::EngineAPI &api )
{
    m_world.update(api);

    for (auto *craft: m_aircraft)
    {
        craft->update(api);
    //     craft->render(api);
    }

}


