#include "plane.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKGraphics/terrain/terrain.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKPhysics/IDKPhysics.hpp>
#include <libidk/idk_math.hpp>


static idk::phys::Airfoil *A0, *A1;


idk::FighterJet::FighterJet( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Aircraft(api, world, p)
{
    m_body->setMass(1000.0f);
    m_body->setDrag(0.15f);
    m_body->setGravScale(0.0f);

    m_seatpos = glm::vec3(0.0, 3.5, 28.0);

    auto &ecs  = api.getECS();
    auto &msys = ecs.getSystem<idk::ModelSys>();

    ecs.setGameObjectName(m_obj, "FighterJet");
    msys.assignModel(m_obj,  "assets/models/fighter-body.idkvi");


    auto &pw = *(world.physworld);
    A0 = pw.createBody<phys::Airfoil>(glm::vec3(-6, 24, 0));
    A1 = pw.createBody<phys::Airfoil>(glm::vec3(+6, 24, 0));

    A0->setGravScale(0.0f);
    A1->setGravScale(0.0f);

    // m_body->addChild(A0);
    // m_body->addChild(A1);

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

    float throttle = 2048.0f * m_ctl.throttle;
    float pitch    = 256.0f  * m_ctl.roll;
    float roll     = 256.0f  * m_ctl.roll;
    float yaw      = 128.0f  * m_ctl.roll;

    m_body->applyForceLinear(throttle * m_body->getFront());
    m_body->applyForceAngular(pitch * m_body->getRight());
    m_body->applyForceAngular(roll * m_body->getFront());
    m_body->applyForceAngular(yaw * m_body->getUp());


    for (auto *B: m_body->m_children)
    {
        auto T0  = B->getRenderMatrix(true);
        auto T1  = B->getRenderMatrixPrev(true);
        ren.drawRect(T0, T1);
    }
}



glm::vec3
idk::FighterJet::getSeatPosition() const
{
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    return tsys.getModelMatrix(m_obj) * glm::vec4(m_seatpos, 1.0);
}
