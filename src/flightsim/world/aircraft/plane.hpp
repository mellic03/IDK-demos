#pragma once

#include <flightsim/world/aircraft/aircraft.hpp>
#include <IDKPhysics/body/rigidbody.hpp>


namespace idk
{
    class FighterJet;
}




class idk::FighterJet: public idk::Aircraft
{
private:

public:

    FighterJet( idk::EngineAPI&, idk::World&, const glm::vec3& );
    virtual void update() override;

    virtual glm::vec3 getSeatPosition() const override;

};