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
    ecs.giveComponent<evo::PlayerCmp>(m_obj).player = this;

    auto &ssys = ecs.getSystem<idk::ScriptSys>();
    // ssys.attachScript(m_obj, "assets/scripts/player-look", static_cast<void*>(&m_ctl));
    // ssys.attachScript(m_obj, "assets/scripts/player-move", static_cast<void*>(&m_ctl));
    // ssys.attachScript(m_obj, "assets/scripts/player-zoom", static_cast<void*>(&m_ctl));
    // ssys.attachScript(m_obj, "assets/scripts/player-inventory", static_cast<void*>(&m_ctl));

    equipTool(world.createItem<idk::WeaponFlashlight>());

    m_weapons[0] = world.createItem<idk::WeaponHands>();
    m_weapons[1] = world.createItem<idk::WeaponSten>();
    m_weapons[2] = world.createItem<idk::WeaponAK47>();
    m_weapons[3] = world.createItem<idk::WeaponAR15>();
    m_weapons[4] = world.createItem<idk::WeaponRem700>();
    m_ctl.equip_idx = 2;

    _setupKeyboardCallbacks();
    _setupGamepadCallbacks();
}



evo::Player::~Player()
{
    auto &io = m_api.getIO();

    for (int id: m_callbacks)
    {
        io.removeCallback(id);
    }
}



void
evo::Player::update()
{
    using namespace idk;

    auto &io   = m_api.getIO();
    auto &ecs  = m_api.getECS();
    auto &ren  = m_api.getRenderer();
    auto &tsys = ecs.getSystem<idk::TransformSys>();
    float dt   = m_api.dtime();

    this->prompt = "";


    if (io.keyTapped(Keycode::ESCAPE))
        io.mouseCapture(!io.mouseCaptured());
    if (io.mouseCaptured())
        _keyboardControl();
    else
        _gamepadControl();

    Character::update();

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
            m_weapon = nullptr;
        }

        m_equip_idx = m_ctl.equip_idx;
        m_equip_idx = glm::clamp(m_equip_idx, 0, 4);

        m_weapons[m_equip_idx]->setOwner(this);
        m_weapons[m_equip_idx]->show();
        m_weapon = m_weapons[m_equip_idx];
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
evo::Player::_keyboardControl()
{
    using namespace idk;

    auto &io = m_api.getIO();
    float dt = m_api.dtime();

    auto delta = glm::vec3(0.0f);
    float speed = dt * 8.0f;

    if (io.keyDown(idk::Keycode::W))     delta.z -= 1.0f;
    if (io.keyDown(idk::Keycode::S))     delta.z += 1.0f;
    if (io.keyDown(idk::Keycode::A))     delta.x -= 1.0f;
    if (io.keyDown(idk::Keycode::D))     delta.x += 1.0f;

    if (io.keyDown(idk::Keycode::SPACE)) delta.y += 1.0f;
    if (io.keyDown(idk::Keycode::LCTRL)) delta.y -= 1.0f;
    m_ctl.dmove = speed*delta;


    float factor = 0.0f;
    if (io.keyDown(idk::Keycode::Z))
        factor = 1.0f;
    m_ctl.zoom_factor = idk::flerp(m_ctl.zoom_factor, factor, dt, 0.25f);


    if (m_weapon)
    {
        if (io.mouseDown(idkio::IDX_MOUSE_RIGHT))
            m_weapon->aim();
        else
            m_weapon->unaim();

        if (io.mouseDown(idkio::IDX_MOUSE_LEFT) && m_weapon->canFire())
            m_weapon->fire();
    }
}



void
evo::Player::_gamepadControl()
{
    using namespace idk;

    auto &io   = m_api.getIO();
    float dt   = m_api.dtime();
    auto &gpad = io.getGamepad();

    if (gpad.isOpen() == false)
    {
        return;
    }

    glm::vec3 lstick = 0.25f * glm::vec3(gpad.lstick.x, 0.0f, gpad.lstick.y);
    glm::vec3 rstick = -glm::vec3(gpad.rstick.x, gpad.rstick.y, 0.0f);

    m_ctl.dmove = idk::flerp(m_ctl.dmove, lstick, dt, m_ctl.move_growth);
    m_ctl.dlook = idk::flerp(m_ctl.dlook, rstick, dt, m_ctl.look_growth);

    if (io.gamepadButtonDown(Gamepad::BTN_A))
        m_ctl.dmove.y = idk::flerp(m_ctl.dmove.y, +0.25f, m_api.dtime(), m_ctl.move_growth);

    else if (io.gamepadButtonDown(Gamepad::BTN_B))
        m_ctl.dmove.y = idk::flerp(m_ctl.dmove.y, -0.25f, m_api.dtime(), m_ctl.move_growth);


    float factor = 0.0f;
    if (io.gamepadButtonDown(Gamepad::BTN_RSHOULDER))
        factor = 1.0f;
    m_ctl.zoom_factor = idk::flerp(m_ctl.zoom_factor, factor, dt, 0.25f);
    

    if (m_weapon)
    {
        if (gpad.ltrigger.x > 0.25f)
            m_weapon->aim();
        else
            m_weapon->unaim();

        if (gpad.rtrigger.x > 0.25f && m_weapon->canFire())
            m_weapon->fire();
    }

}




void
evo::Player::_setupKeyboardCallbacks()
{
    using namespace idk;
    auto &io = m_api.getIO();

    int id0 = io.onMouseMotion([this](float x, float y) {
        if (m_api.getIO().mouseCaptured())
        {
            float dt = m_api.dtime();
            m_ctl.dlook = 0.00275f * -glm::vec3(x, y, 0.0f);
        }
    });

    m_callbacks.push_back(id0);
}


void
evo::Player::_setupGamepadCallbacks()
{
    using namespace idk;
    auto &io = m_api.getIO();

    int id0 = io.onGamepadButton(IO::GPAD_TAP, [this](uint32_t btn) {
        if (btn == Gamepad::BTN_B)
        {
            m_ctl.crouching = !m_ctl.crouching;
        }
    });

    m_callbacks.push_back(id0);
}








void
evo::Player::look( const glm::vec3 &delta )
{
    auto &ecs = m_api.getECS();
    auto &tsys = ecs.getSystem<idk::TransformSys>();

    tsys.getTransformCmp(m_obj).yaw   += delta.x;
    tsys.getTransformCmp(m_cam).pitch += delta.y;
}


void
evo::Player::move( const glm::vec3 &delta )
{
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
