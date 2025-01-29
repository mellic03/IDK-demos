#include "npc.hpp"
#include <flightsim/world/world/world.hpp>

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>


idk::NPC::NPC( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   Character(api, world, p)
{
    api.getECS().setGameObjectName(m_obj, "NPC");
    m_model = api.getRenderer().loadModel("assets/models/head.idkvi");
}


void
idk::NPC::update()
{
    Character::update();

    auto &ren = m_api.getRenderer();
    auto &tsys = m_api.getECS().getSystem<idk::TransformSys>();

    glm::vec3 pos = getWorldPosition();

    glm::mat4 M1 = tsys.getTransformCmp(m_obj).model;
    glm::mat4 M2 = tsys.getTransformCmp(m_obj).prev_model;

    glm::vec3 head = glm::vec3(0.0, 1.3, -0.3);
    glm::mat4 T = glm::translate(glm::mat4(1), head);
    glm::mat4 S = glm::scale(glm::mat4(1), glm::vec3(1.85));

    ren.drawSphere(pos, 1.0f);
    ren.drawModel(m_model, M1*T*S, M2*T*S);
}


