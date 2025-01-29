#include "player.hpp"
#include <flightsim/world/weapon/weapon.hpp>
#include <flightsim/world/world/world.hpp>
#include <flightsim/world/world/vehicle.hpp>

#include <IDKGameEngine/IDKGameEngine.hpp>
#include <IDKIO/IDKIO.hpp>
#include <IDKBuiltinCS/sys-audio.hpp>
#include <IDKBuiltinCS/sys-camera.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKBuiltinCS/sys-script.hpp>
#include <libidk/idk_math.hpp>



evo::Player::Player( idk::EngineAPI &api, idk::World &world, const glm::vec3 &p )
:   idk::Character(api, world, p),
    m_cam(m_head_obj)
{
    auto &ecs  = api.getECS();
    auto &asys = ecs.getSystem<idk::AudioSys>();
    auto &tsys = ecs.getSystem<idk::TransformSys>();

    m_cam = ecs.createGameObject("Camera", false);
    ecs.giveChild(m_obj, m_cam);
    tsys.getLocalPosition(m_cam) = glm::vec3(0.0f);

    ecs.setGameObjectName(m_obj, "Player");
    ecs.giveComponent<idk::CameraCmp>(m_cam);
    ecs.giveComponent<idk::ScriptCmp>(m_obj);
    ecs.giveComponent<idk::AudioListenerCmp>(m_cam);

    auto &ssys = ecs.getSystem<idk::ScriptSys>();
    ssys.attachScript(m_obj, "assets/scripts/player-look", static_cast<void*>(&m_ctl));
    ssys.attachScript(m_obj, "assets/scripts/player-move", static_cast<void*>(&m_ctl));
    ssys.attachScript(m_obj, "assets/scripts/player-zoom", static_cast<void*>(&m_ctl));
    ssys.attachScript(m_obj, "assets/scripts/player-inventory", static_cast<void*>(&m_ctl));

    equipTool(world.createItem<idk::WeaponFlashlight>());

    m_weapons[0] = world.createItem<idk::WeaponHands>();
    m_weapons[1] = world.createItem<idk::WeaponSten>();
    m_weapons[2] = world.createItem<idk::WeaponAK47>();
    m_weapons[3] = world.createItem<idk::WeaponAR15>();
    m_weapons[4] = world.createItem<idk::WeaponRem700>();
}



// #define do_thing(key, weapon_type) \
//     if (io.keyTapped(key)) { \
//         P->m_callbacks.push_back([P](){ \
//             if (P->equippedItem()) { \
//                 P->getWorld().removeItem(P->equippedItem()); \
//             } \
//             P->equipItem(P->getWorld().createItem<weapon_type>()); \
//         }); \
//     } \
// \



void
evo::Player::update()
{
    this->move(m_ctl.dmove);
    this->look(m_ctl.dlook);
    Character::update();

    for (auto &fn: m_callbacks)
    {
        fn();
    }
    m_callbacks.clear();

    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &ren  = m_api.getRenderer();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    this->prompt = "";

    if (io.mouseCaptured() == false)
    {
        return;
    }


    {
        auto &cmp = ecs.getComponent<idk::CameraCmp>(m_cam);
        auto &cam = ren.getCamera(cmp.cam_id);
        cam.fov = glm::mix(m_ctl.rest_fov, m_ctl.zoom_fov, m_ctl.zoom_factor);
    }

    if (io.keyPressed(idk::Keycode::F))
    {
        m_tool->fire();
    }

    if (m_equip_idx != m_ctl.equip_idx)
    {
        if (m_weapons[m_equip_idx])
        {
            m_weapons[m_equip_idx]->hide();
        }

        m_equip_idx = m_ctl.equip_idx;
        m_equip_idx = glm::clamp(m_equip_idx, 0, 4);

        m_weapons[m_equip_idx]->setOwner(this);
        m_weapons[m_equip_idx]->show();
    }

    auto *W = dynamic_cast<idk::Weapon*>(m_weapons[m_equip_idx]);

    if (W)
    {
        W->setOwner(this);

        if (io.mouseDown(idk::IO::RMOUSE))
        {
            W->aim();
        }
        else
        {
            W->unaim();
        }

        if (io.mouseDown(idk::IO::LMOUSE))
        {
            if (W->fire())
            {
                crosshair_scale = idk::flerp(crosshair_scale, 4.0f, dt, 0.1f);
            }
        }
    }

    crosshair_scale = idk::flerp(crosshair_scale, 1.0f, dt, 0.25f);
    
    
    
    if (this->vehicle)
    {
        if (io.keyTapped(idk::Keycode::E))
        {
            this->vehicle->undrive();
        }
    }

    else
    {
        for (auto *V: m_world.vehicles())
        {
            glm::vec3 A = this->getWorldPosition();
            glm::vec3 B = V->getSeatPosition();

            if (glm::distance(A, B) < 2.0f)
            {
                this->prompt = "[E] Drive vehicle";

                if (io.keyTapped(idk::Keycode::E))
                {
                    V->drive(this);
                    break;
                }
            }
        }
    }

}



void
evo::Player::look( const glm::vec3 &delta )
{
    Character::look(delta);

    auto &ecs = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();

    tsys.getTransformCmp(m_obj).yaw   += delta.x;
    tsys.getTransformCmp(m_cam).pitch += delta.y;
}


void
evo::Player::move( const glm::vec3 &delta )
{
    Character::move(delta);

    auto &ecs = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();

    glm::mat3 R = glm::mat3(tsys.getModelMatrix(m_cam));
    tsys.getLocalPosition(m_obj) += R*delta;
}


void
evo::Player::push( const glm::vec3 &force )
{
    Character::push(force);
    auto &ecs = m_api.getECS();
}


glm::vec3
evo::Player::getCameraFront()
{
    auto &tsys = m_api.getECS().getSystem<idk::TransformSys>();
    return tsys.getFront(m_cam);
}



idk::WeaponFlashlight*
evo::Player::equippedTool()
{
    return m_tool;
}


void
evo::Player::equipTool( idk::WeaponFlashlight *I )
{
    I->setOwner(this);
    m_tool = I;
}
