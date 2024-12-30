#pragma once
#include "physics/physicsworld.hpp"
#include "physics/rigidbody.hpp"
#include "aircraft.hpp"


namespace idk
{
    class EngineAPI;
}


class FlightSim
{
private:
    fsim::PhysicsWorld m_world;
    std::vector<fsim::Aircraft*> m_aircraft;

public:
    fsim::Aircraft *m_craft;

         FlightSim();

    void setup( idk::EngineAPI& );
    void mainloop( idk::EngineAPI& );


    template <typename T, typename... Args>
    fsim::Aircraft *createAircraft( Args&&... args )
    {
        auto *obj = new T(std::forward<Args>(args)...);
        m_aircraft.push_back(dynamic_cast<fsim::Aircraft*>(obj));
        return obj;
    }
};

