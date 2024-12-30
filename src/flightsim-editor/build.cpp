#include "game.hpp"

#include <filesystem>
#include <libidk/idk_platform.hpp>
#include <libidk/idk_cppscript.hpp>


static void
build_scripts( const std::string &script_path )
{
    namespace fs = std::filesystem;
    auto dir_iter = fs::directory_iterator(script_path);

    fs::create_directory("./assets/script_dlib/");

    std::vector<idk::RuntimeScript*> scripts;
    std::vector<std::string>         dst_paths;

    for (const auto &entry: dir_iter)
    {
        auto src_path = entry.path().filename().stem();
        auto dst_path = fs::path("./assets/script_dlib/") / entry.path().filename();
        dst_path.replace_extension(IDK_DLIB_EXT);

        auto script = idk::RuntimeScript(src_path.string(), false);
        script.saveLib(dst_path);
    }

}



void DemoFlightsimEditor::build()
{
    std::cout << "[DemoFlightsimEditor::build]\n";
    build_scripts("./assets/scripts/");

}
