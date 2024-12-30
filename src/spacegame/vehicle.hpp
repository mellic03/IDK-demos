#pragma once

#include <IDKECS/IDKECS.hpp>
#include <IDKBuiltinCS/IDKBuiltinCS.hpp>


namespace sp
{
    class VehicleSys;
    struct VehicleCmp;
}




class sp::VehicleSys: public idk::ECS::System
{
private:

public:
    virtual void    init   ( idk::EngineAPI & ) final {  };
    virtual void    update ( idk::EngineAPI & ) final;

};



struct sp::VehicleCmp
{
    int obj_id = -1;

    size_t  serialize            ( std::ofstream &stream ) const;
    size_t  deserialize          ( std::ifstream &stream );
    static void onObjectAssignment   ( idk::EngineAPI &api, int obj_id );
    static void onObjectDeassignment ( idk::EngineAPI &api, int obj_id );
    static void onObjectCopy         ( int src_obj, int dst_obj );
};


