#include "helicopter.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>
#include <print>


idk::Helicopter::Helicopter( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Aircraft(api, world, p)
{
    m_body->state.invMass = 1.0f / 128.0f; // ->setMass(8.0f);
    m_body->state.restitution = 0.45f;
    m_body->state.drag = 0.25f;
    m_body->shape.extents = glm::vec3(4.0f);
    m_body->shape.radius = 4.0f;

    auto &pw = *(world.physworld);

    auto *B0 = pw.createBody<phys::RigidBody>(6.0f * glm::vec3(-1,  0.01,  0) + glm::vec3(0, 128, 0));
    // auto *B1 = pw.createBody<phys::RigidBody>(6.0f * glm::vec3(+1,  0.02,  0) + glm::vec3(0, 128, 0));
    // auto *B2 = pw.createBody<phys::RigidBody>(6.0f * glm::vec3( 0, -0.1,  -1) + glm::vec3(0, 128, 0));
    // auto *B3 = pw.createBody<phys::RigidBody>(6.0f * glm::vec3( 0, +0.02, +1) + glm::vec3(0, 128, 0));


    // B0->applyImpulseLinear(-0.5f*B0->state.pos);
    // B1->applyImpulseLinear(-0.5f*B1->state.pos);
    // B2->applyImpulseLinear(-0.5f*B2->state.pos);
    // B3->applyImpulseLinear(-0.5f*B3->state.pos);

    // pw.createConstraint<phys::SpringConstraint>(m_body, B0, glm::vec3(-8, -12,  8), 0.25, 0.4);
    // pw.createConstraint<phys::SpringConstraint>(m_body, B1, glm::vec3(+8, -12,  8), 0.25, 0.4);
    // pw.createConstraint<phys::SpringConstraint>(m_body, B2, glm::vec3(-8, -12, -8), 0.25, 0.4);
    // pw.createConstraint<phys::SpringConstraint>(m_body, B3, glm::vec3(+8, -12, -8), 0.25, 0.4);

    // m_body->addChild(B0);
    // m_body->addChild(B1);
    // m_body->addChild(B2);
    // m_body->addChild(B3);

    // B0->setMass(2);
    // B2->setMass(2);
    // B3->setMass(2);
    // B3->setMass(2);


    auto &ecs  = api.getECS();
    auto &msys = ecs.getSystem<idk::ModelSys>();
    auto &ssys = ecs.getSystem<idk::ScriptSys>();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    ecs.setGameObjectName(m_obj, "Helicopter");

    m_top   = ecs.createGameObject("Top", false);
    m_rear  = ecs.createGameObject("Rear", false);

    ecs.giveChild(m_obj, m_top);
    ecs.giveChild(m_obj, m_rear);
    tsys.getLocalPosition(m_top) = glm::vec3(0.0, 0.0, 0.56);
    tsys.getLocalPosition(m_rear) = glm::vec3(0.0, 11.02, -34.27);

    msys.assignModel(m_obj,  "assets/models/helicopter-body.idkvi");
    msys.assignModel(m_top,  "assets/models/helicopter-top.idkvi");
    msys.assignModel(m_rear, "assets/models/helicopter-rear.idkvi");

}


void
idk::Helicopter::update()
{
    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &ren  = m_api.getRenderer();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    tsys.rotateLocalAxis(m_top,  glm::vec3(0, 1, 0), glm::clamp(m_ctl.throttle, 0.5f, 4.0f));
    tsys.rotateLocalAxis(m_rear, glm::vec3(1, 0, 0), glm::clamp(m_ctl.yaw, 0.5f, 4.0f));
    tsys.getTransform(m_obj) = idk::Transform::fromGLM(m_body->getRenderMatrix());

    // ren.drawSphere(m_body->state.COM_world 8.0f);


    glm::vec3 vel = m_body->state.linear.vel;
    glm::vec3 up  = glm::mix(m_body->state.up, m_body->state.front, 0.1f);
    float     th  = 1.0f;

    if (glm::length2(vel) > 0.0f)
    {
       th = glm::dot(up, vel) / glm::length(vel);
    }


    float roll_force  = 0.0f;
    float pitch_force = 0.0f;
    float yaw_force   = 0.0f;
    float throttle    = 0.0f;


    if (this->driver)
    {
        roll_force  = 1.0f * m_ctl.roll;
        pitch_force = 1.0f * m_ctl.pitch;
        yaw_force   = 1.0f * m_ctl.yaw;
        throttle    = 2048.0f * m_ctl.throttle;
        // throttle    = (1.0f / m_body->state.invMass) * 9.8 * 1.75 * m_ctl.throttle; // * (9.81 * 2.0f * m_ctl.throttle);

        if (io.m_joystick_jhat[0] == 1) m_cam_pitch -= 0.35;
        if (io.m_joystick_jhat[0] == 4) m_cam_pitch += 0.35;
        if (io.m_joystick_jhat[0] == 8) m_cam_yaw -= 0.35;
        if (io.m_joystick_jhat[0] == 2) m_cam_yaw += 0.35;

        int cam = this->driver->headObjID();
        tsys.getTransformCmp(cam).pitch = -m_cam_pitch;
        tsys.getTransformCmp(cam).yaw   = -m_cam_yaw;

        if (io.m_joystick_btndown[0] == true)
        {
            tsys.getLocalPosition(cam) = glm::vec3(0.0, -8.0, 16.0);
        }

        else
        {
            tsys.getLocalPosition(cam) = glm::vec3(0.0, 0.0, 0.0);
        }
    }


    static float accum = 0.0f;
    accum += dt;
    auto &PW = m_world.physworld;

    while (accum > 1.0f / PW->config.tickrate)
    {
        auto yaw_pos   = tsys.getWorldPosition(m_rear);
        auto roll_pos  = tsys.getWorldPosition(m_top) + m_body->state.up;
        auto pitch_pos = tsys.getWorldPosition(m_obj) - m_body->state.front;

        m_body->applyForceLinear(throttle * m_body->state.up);
    
        m_body->applyForceAngular(yaw_force * m_body->state.up);
        m_body->applyForceAngular(roll_force * -m_body->state.front);
        m_body->applyForceAngular(pitch_force * m_body->state.right);

        accum -= 1.0f / PW->config.tickrate;
    }

}




glm::vec3
idk::Helicopter::getSeatPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getModelMatrix(m_obj) * glm::vec4(m_seatpos, 1.0);
}
