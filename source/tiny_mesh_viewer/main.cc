#include <cstdlib>
#include <filesystem>
#include <iostream>

#include "cxxopts.hpp"

#include "tiny_mesh_viewer/app.h"
#include "tiny_mesh_viewer/common/logging.h"

int main(int argc, char** argv) {
  auto options = cxxopts::Options(/*program_name=*/"viewer",
                                  /*help_string=*/"A tiny mesh viewer.");
  options.add_options()(/*name=*/"c,config", /*desc=*/"Config file.",
                        /*value=*/
                        cxxopts::value<std::filesystem::path>()->default_value(
                            std::filesystem::current_path() / "config.yaml"),
                        /*arg_help=*/"PATH")(
      /*name=*/"h,help", /*desc=*/"Show this message and exit.",
      /*value=*/cxxopts::value<bool>()->default_value("false"));
  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return EXIT_SUCCESS;
  }
  try {
    auto config = result["config"].as<std::filesystem::path>();
    auto app = std::make_unique<tiny_mesh_viewer::App>(YAML::LoadFile(config));
    app->Run();
  } catch (const std::exception& e) {
    ERROR("{}", e.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
