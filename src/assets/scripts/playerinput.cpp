#include <iostream>
#include <IDKGameEngine/IDKGameEngine.hpp>

extern "C"
{
    int idk_ScriptMain( idk::EngineAPI &api, int obj_id, int other_id )
    {
        std::cout << "FUCK YEAH\n";
        return 0;
    }
}
