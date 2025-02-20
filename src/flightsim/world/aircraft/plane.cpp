#include "plane.hpp"
#include "airfoil.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>


static idk::Airfoil *A0, *A1;


idk::FighterJet::FighterJet( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Aircraft(api, world, p)
{
    m_body->state.invMass = 1.0f / 32.0f;
    m_body->state.drag = 0.01f;
    m_body->shape.radius = 4.15f;

    m_seatpos = glm::vec3(0.0, 3.5, 28.0);

    auto &ecs  = api.getECS();
    auto &msys = ecs.getSystem<idk::ModelSys>();

    ecs.setGameObjectName(m_obj, "FighterJet");
    msys.assignModel(m_obj,  "assets/models/fighter-body.idkvi");

    auto &pw = *(world.physworld);
    A0 = new idk::Airfoil(pw);
    A1 = new idk::Airfoil(pw);
    
    A0->localpos = glm::vec3(-16, 0, 1);
    A1->localpos = glm::vec3(+16, 0, 1);
}


void
idk::FighterJet::update()
{
    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &ren  = m_api.getRenderer();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    tsys.getTransform(m_obj) = idk::Transform::fromGLM(m_body->getRenderMatrix());

    ren.drawRect(A0->getRenderMatrix(m_body->state.T));
    ren.drawRect(A1->getRenderMatrix(m_body->state.T));


    if (this->driver)
    {
        static float m_cam_pitch = 0.0f;
        static float m_cam_yaw   = 0.0f;

        if (io.m_joystick_jhat[0] == 1) m_cam_pitch -= 0.35;
        if (io.m_joystick_jhat[0] == 4) m_cam_pitch += 0.35;
        if (io.m_joystick_jhat[0] == 8) m_cam_yaw -= 0.35;
        if (io.m_joystick_jhat[0] == 2) m_cam_yaw += 0.35;

        int cam = this->driver->headObjID();
        tsys.getTransformCmp(cam).pitch = -m_cam_pitch;
        tsys.getTransformCmp(cam).yaw   = -m_cam_yaw;

        if (io.m_joystick_btndown[0] == true)
        {
            tsys.getLocalPosition(cam) = glm::vec3(0.0, 8.0, 64.0);
        }

        else
        {
            tsys.getLocalPosition(cam) = glm::vec3(0.0, 0.0, 0.0);
        }
    }
}



void
idk::FighterJet::fixedUpdate( float timestep )
{
    if (this->driver == nullptr)
    {
        return;
    }

    float throttle = 128.0f * m_ctl.throttle;
    float pitch    = 1.0f   * m_ctl.pitch;
    float roll     = 1.0f   * (m_ctl.roll+0.5f); // [0, 1] range
    float yaw      = 1.0f   * m_ctl.yaw;

    m_body->applyForceLinear(throttle * m_body->state.front);
    m_body->applyForceAngular(pitch * m_body->state.right);
    // m_body->applyForceAngular(-roll * m_body->state.front);
    // m_body->applyForceAngular(yaw * m_body->state.up);

    A0->wingAngle = roll;
    A1->wingAngle = -roll;

    glm::vec3 aero0 = A0->computeAeroForcesLinear(m_body->state.T);
    glm::vec3 aero1 = A1->computeAeroForcesLinear(m_body->state.T);

    m_body->applyForceLinear(aero0 + aero1);
    m_body->applyForceAngular(aero0, A0->worldpos);
    m_body->applyForceAngular(aero1, A1->worldpos);

}



glm::vec3
idk::FighterJet::getSeatPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getModelMatrix(m_obj) * glm::vec4(m_seatpos, 1.0);
}
