#include "weapon.hpp"
#include "../world/character.hpp"

#include <IDKGraphics/IDKGraphics.hpp>
#include <IDKECS/IDKECS.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKBuiltinCS/sys-audio.hpp>
#include <IDKBuiltinCS/sys-lightsource.hpp>
#include <IDKBuiltinCS/sys-model.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <libidk/idk_math.hpp>
#include <libidk/idk_random.hpp>


idk::Weapon::Weapon( idk::EngineAPI &api, World &world, const idk::string &name,
                     const idk::string &model, const idk::string &audio )
:   Item(api, world),
    curr_pos(0.0),
    curr_rot(0.0)
{
    auto &ecs  = api.getECS();
    auto &asys = ecs.getSystem<idk::AudioSys>();
    auto &msys = ecs.getSystem<idk::ModelSys>();

    ecs.setGameObjectName(m_obj, name.c_str());
    ecs.giveComponent<idk::AudioEmitterCmp>(m_obj);
    asys.assignSound(m_obj, audio.c_str());

    if (model != "")
    {
        msys.assignModel(m_obj, model.c_str());
    }

    // auto &ssys = ecs.getSystem<idk::ScriptSys>();
    // ssys.attachScript(m_obj, "assets/scripts/weapon-sway", dynamic_cast<void*>(this));
    // ssys.attachScript(m_obj, "assets/scripts/weapon-fire", dynamic_cast<void*>(this), false);
}


idk::Weapon::~Weapon()
{
    // auto &ecs  = m_api.getECS();
    // auto &ssys = ecs.getSystem<idk::ScriptSys>();
    // auto &cmp  = ecs.getComponent<idk::ScriptCmp>(m_obj);

    // for (int i=0; i<cmp.autoexec.size(); i++)
    // {
    //     cmp.autoexec[i] = false;
    // }

    // ecs.removeComponent<idk::ScriptCmp>(m_obj);
}


void
idk::Weapon::setOwner(Character *owner )
{
    Item::setOwner(owner);
    m_api.getECS().giveChild(m_owner->headObjID(), m_obj);
}


void
idk::Weapon::update()
{
    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &asys = ecs.getSystem<idk::AudioSys>();
    auto &msys = ecs.getSystem<idk::ModelSys>();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    if (m_owner)
    {
        _sway(m_api);
    }

    tsys.getXYZScale(m_obj) = glm::vec3(m_conf.scale);

    m_timer = glm::max(m_timer-dt, 0.0f);
}


void idk::Weapon::show()
{
    auto &ecs = m_api.getECS();
    if (ecs.hasComponent<idk::ModelCmp>(m_obj))
    {
        ecs.getComponent<idk::ModelCmp>(m_obj).visible = true;
    }
}

void idk::Weapon::hide()
{
    auto &ecs = m_api.getECS();
    if (ecs.hasComponent<idk::ModelCmp>(m_obj))
    {
        ecs.getComponent<idk::ModelCmp>(m_obj).visible = false;
    }
}




void
idk::Weapon::fire()
{
    if (m_timer <= 0.0f)
    {
        auto &ecs  = m_api.getECS();
        auto &asys = ecs.getSystem<idk::AudioSys>();
        auto &ssys = ecs.getSystem<idk::ScriptSys>();
        // ssys.executeScript(m_obj, "weapon-fire", dynamic_cast<void*>(this));

        asys.playSound(m_obj, false);
        glm::vec3 recoil = m_conf.recoil;

        float rx = idk::randf(-1, +1) * recoil.x;
        float ry = idk::randf(-1, +1) * recoil.y;
        float rz = idk::randf(0.8, 1.2) *recoil.z;
        this->sway_pos += glm::vec3(rx, ry, rz);

        m_timer = m_conf.cooldown;
    }
}


void
idk::Weapon::_sway( idk::EngineAPI &api )
{
    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    auto  rest_pos   = m_conf.rest_pos;
    auto  rest_spd   = m_conf.rest_spd;
    auto  rest_rot   = m_conf.rest_rot;

    auto  aim_rot    = m_conf.aim_rot;
    auto  aim_pos    = m_conf.aim_pos;

    auto &sway_pos   = this->sway_pos;
    auto  sway_spd   = m_conf.sway_spd;

    auto &curr_pos   = this->curr_pos;
    auto &curr_rot   = this->curr_rot;

    glm::vec3 target_pos;
    glm::vec3 target_rot;

    if (isAiming())
    {
        target_pos = aim_pos;
        curr_rot   = aim_rot;
        sway_spd   = glm::vec3(0.05f);
        rest_spd   = glm::vec3(0.0025f);
        tsys.getTransformCmp(m_obj).pitch = aim_rot.x;
        tsys.getTransformCmp(m_obj).yaw   = aim_rot.y;
        tsys.getTransformCmp(m_obj).roll  = aim_rot.z;
    }

    else
    {
        target_pos = rest_pos;
        curr_rot   = rest_rot;
        tsys.getTransformCmp(m_obj).pitch = rest_rot.x;
        tsys.getTransformCmp(m_obj).yaw   = rest_rot.y;
        tsys.getTransformCmp(m_obj).roll  = rest_rot.z;
    }

    glm::vec3 dlook = m_owner->dlook();
    glm::vec3 dmove = m_owner->dmove();

    sway_pos += dt * dlook * sway_spd * glm::vec3(1, -1, 0);

    for (int i=0; i<3; i++)
    {
        sway_pos[i] = idk::flerp(sway_pos[i], 0.0f, dt, 0.25f);
        curr_pos[i] = idk::flerp(curr_pos[i], target_pos[i], dt, 0.25f);
        curr_rot[i] = idk::flerp(curr_rot[i], target_rot[i], dt, 0.25f);
    }

    tsys.getLocalPosition(m_obj) = curr_pos + sway_pos;
}
