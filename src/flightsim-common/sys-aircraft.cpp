#include "sys-aircraft.hpp"



void
fsim::AircraftSys::update( idk::EngineAPI &api )
{
    
}





size_t
fsim::ControlSurfaceCmp::serialize( std::ofstream &stream ) const
{
    size_t n = 0;
    n += idk::streamwrite(stream, obj_id);
    return n;
}


size_t
fsim::ControlSurfaceCmp::deserialize( std::ifstream &stream )
{
    size_t n = 0;
    n += idk::streamread(stream, obj_id);
    return n;
}


void
fsim::ControlSurfaceCmp::onObjectAssignment( idk::EngineAPI &api, int obj_id )
{
    auto &cmp = idk::ECS2::getComponent<ControlSurfaceCmp>(obj_id);
}


void
fsim::ControlSurfaceCmp::onObjectDeassignment( idk::EngineAPI &api, int obj_id )
{

}


void
fsim::ControlSurfaceCmp::onObjectCopy( int src_obj, int dst_obj )
{
    auto &src = idk::ECS2::getComponent<ControlSurfaceCmp>(src_obj);
    auto &dst = idk::ECS2::getComponent<ControlSurfaceCmp>(dst_obj);
    

}
