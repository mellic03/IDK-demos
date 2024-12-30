#include "vehicle.hpp"
#include <IDKGameEngine/IDKGameEngine.hpp>


void
sp::VehicleSys::update( idk::EngineAPI &api )
{
    for (auto &cmp: idk::ECS2::getComponentArray<VehicleCmp>())
    {
        
    }

}





size_t
sp::VehicleCmp::serialize( std::ofstream &stream ) const
{
    size_t n = 0;

    return n;
}


size_t
sp::VehicleCmp::deserialize( std::ifstream &stream )
{
    size_t n = 0;

    return n;
}

void
sp::VehicleCmp::onObjectAssignment( idk::EngineAPI &api, int obj_id )
{

}


void
sp::VehicleCmp::onObjectDeassignment( idk::EngineAPI &api, int obj_id )
{

}


void
sp::VehicleCmp::onObjectCopy( int src_obj, int dst_obj )
{

}


