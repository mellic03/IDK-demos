#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <demo-common/actor.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    float dt = api.dtime();
    idk::Actor *A = static_cast<idk::Actor*>(data);

    static glm::vec2 md = glm::vec2(0.0f);

    float alpha = glm::clamp(16.0f*dt, 0.0f, 1.0f);
    md += 0.01f * -idkio::mouseDelta();
    md = glm::mix(md, glm::vec2(0.0f), alpha);

    A->look(md);

    return 0;
}
