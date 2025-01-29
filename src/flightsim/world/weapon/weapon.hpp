#pragma once
#include <flightsim/world/world/item.hpp>
#include <libidk/idk_string.hpp>

namespace idk
{
    struct WeaponConfig;
    class Weapon;
    class WeaponHands;
    class WeaponAR15;
    class WeaponAK47;
    class WeaponSten;
    class WeaponRem700;
    class WeaponFlashlight;
}


struct idk::WeaponConfig
{
    glm::vec3 rest_pos = glm::vec3(0.3, -0.3, -0.45);
    glm::vec3 rest_rot = glm::vec3(0.0);
    glm::vec3 rest_spd = glm::vec3(0.2);

    glm::vec3 sway_spd = glm::vec3(1.0);

    glm::vec3 aim_pos  = glm::vec3(0.0);
    glm::vec3 aim_rot  = glm::vec3(0.0);
    float     aim_fov  = 45.0f;

    float     cooldown = 1.0f / 4.0f;
    glm::vec3 recoil   = glm::vec3(0.02, 0.02, 0.2);
    float     scale    = 0.1f;

    idk::string model = "";
    idk::string audio = "assets/audio/click.wav";
};


class idk::Weapon: public idk::Item
{
protected:
    WeaponConfig m_conf;
    bool  m_aiming = false;
    float m_timer  = 0.0f;
    void _sway( idk::EngineAPI& );

public:
    glm::vec3 sway_pos = glm::vec3(0.0);
    glm::vec3 curr_pos;
    glm::vec3 curr_rot;

    Weapon( idk::EngineAPI&, World&, const idk::string&, const idk::string&, const idk::string& );
    ~Weapon();

    virtual void update() override;
    virtual void render( idk::RenderEngine& ) override {  };
    virtual void setOwner( Character* ) override;
    WeaponConfig &getConf() { return m_conf; };

    void aim()      { m_aiming = true;  }
    void unaim()    { m_aiming = false; }
    bool isAiming() { return m_aiming;  }

    void show();
    void hide();

    virtual bool fire();

};



class idk::WeaponHands: public idk::Weapon
{
public:
    WeaponHands( idk::EngineAPI&, World& );
};


class idk::WeaponAR15: public idk::Weapon
{
public:
    WeaponAR15( idk::EngineAPI&, World& );
};



class idk::WeaponAK47: public idk::Weapon
{
public:
    WeaponAK47( idk::EngineAPI&, World& );
};



class idk::WeaponSten: public idk::Weapon
{
public:
    WeaponSten( idk::EngineAPI&, World& );
};



class idk::WeaponRem700: public idk::Weapon
{
public:
    WeaponRem700( idk::EngineAPI&, World& );
};



class idk::WeaponFlashlight: public idk::Weapon
{
private:
    bool m_on = false;

public:
    float intensity = 4.0f;

    WeaponFlashlight( idk::EngineAPI&, World& );
    virtual bool fire() final;
};


