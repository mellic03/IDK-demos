#include "game.hpp"

int main( int argc, char **argv )
{
    using namespace idk;
    using lf = idk::log_flag;

    auto &flags = idk::Logger::flags;

    flags  = lf::INFO | lf::WARN | lf::ERROR;
    flags |= lf::DETAIL | lf::DEBUG;
    flags |= lf::RENDER;
    flags |= lf::AUDIO;
    flags |= lf::IO;
    // flags |= lf::EVERYTHING;

    return IDKGameEngineMain(argc, argv, new DemoFlightsim());
}
