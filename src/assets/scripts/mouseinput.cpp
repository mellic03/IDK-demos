#include <iostream>

#include <IDKGameEngine/idk_engine_api.hpp>
#include <IDKBuiltinCS/sys-transform.hpp>
#include <IDKIO/IDKIO.hpp>

#include <demo-common/actor.hpp>


extern "C"
int script( idk::EngineAPI &api, void *data )
{
    float dt = api.dtime();
    auto  *A = static_cast<idk::Actor*>(data);

    // if (idkio::mouseDown(idkio::MMOUSE) == false)
    // {
    //     return 0;
    // }

    auto  md = -idkio::mouseDelta();
    float wd = idkio::mouseWheelDelta();

    A->look(md);

    return 0;
}
