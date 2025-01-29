#pragma once

#include <flightsim/world/aircraft/aircraft.hpp>


namespace idk
{
    class Helicopter;
}




class idk::Helicopter: public idk::Aircraft
{
private:
    int m_top;
    int m_rear;

public:
    float m_cam_pitch = 0.0f;
    float m_cam_yaw   = 0.0f;


    Helicopter( idk::EngineAPI&, idk::World&, const glm::vec3& );
    virtual void update() override;

    // virtual void look( const glm::vec3& ) override;
    // virtual void move( const glm::vec3& ) override;

    virtual glm::vec3 getSeatPosition() const override;

};