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


static idk::Airfoil *A0, *A1, *Tail;


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
    // Tail = new idk::Airfoil(pw);
    
    A0->localpos = glm::vec3(-16, 0, 1);
    A1->localpos = glm::vec3(+16, 0, 1);
    // Tail->localpos = glm::vec3(0, 8, -16);
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
    // ren.drawRect(Tail->getRenderMatrix(m_body->state.T));



    float throttle = 2048.0f * m_ctl.throttle;
    float pitch    = 0.5f  * m_ctl.pitch;
    float roll     = 0.5f   * m_ctl.roll;
    float yaw      = 0.5f  * m_ctl.yaw;

    m_body->applyForceLinear(throttle * m_body->state.front);
    // m_body->applyForceAngular(pitch * m_body->state.right);
    // m_body->applyForceAngular(-roll * m_body->state.front);
    // m_body->applyForceAngular(yaw * m_body->state.up);

    A0->wingAngle = +roll + pitch;
    A1->wingAngle = -roll + pitch;
    // Tail->wingAngle = yaw;

    glm::mat3 Ti3 = glm::mat3(m_body->state.Ti);
    glm::vec3 aero0 = Ti3 * A0->computeAeroForcesLinear(m_body->state.T, m_body->state.measured.vel);
    glm::vec3 aero1 = Ti3 * A1->computeAeroForcesLinear(m_body->state.T, m_body->state.measured.vel);

    // m_body->applyForceLinear(aero0 + aero1);
    m_body->state.applyPointForce(aero0, A0->localpos);
    m_body->state.applyPointForce(aero1, A1->localpos);
    // m_body->applyForceAngular(aero1, A1->worldpos);



    if (this->driver)
    {
        static float curr_pitch = 0.0f;
        static float curr_yaw   = 0.0f;

        curr_pitch = idk::flerp(curr_pitch, m_ctl.cam_pitch, dt, 0.75f);
        curr_yaw   = idk::flerp(curr_yaw, m_ctl.cam_yaw, dt, 0.75f);

        int cam = this->driver->headObjID();
        tsys.getTransformCmp(cam).pitch = -curr_pitch;
        tsys.getTransformCmp(cam).yaw   = -curr_yaw;

        // if (io.m_joystick_btndown[0] == true)
        // {
        //     tsys.getLocalPosition(cam) = glm::vec3(0.0, 8.0, 64.0);
        // }

        // else
        // {
        //     tsys.getLocalPosition(cam) = glm::vec3(0.0, 0.0, 0.0);
        // }
    }
}



void
idk::FighterJet::fixedUpdate( float timestep )
{
    if (this->driver == nullptr)
    {
        return;
    }

}



glm::vec3
idk::FighterJet::getSeatPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getModelMatrix(m_obj) * glm::vec4(m_seatpos, 1.0);
}
