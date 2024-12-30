#pragma once

#include <IDKECS/IDKECS.hpp>


namespace fsim
{
    class AircraftSys;
    struct ControlSurfaceCmp;
};


class fsim::AircraftSys: public idk::ECS::System
{
public:
    virtual void init   ( idk::EngineAPI& ) final {  };
    virtual void update ( idk::EngineAPI& ) final;

};



struct fsim::ControlSurfaceCmp
{
    int obj_id = -1;

    size_t serialize( std::ofstream &stream ) const;
    size_t deserialize( std::ifstream &stream );
    static void onObjectAssignment( idk::EngineAPI &api, int obj_id );
    static void onObjectDeassignment( idk::EngineAPI &api, int obj_id );
    static void onObjectCopy( int src_obj, int dst_obj );

};
