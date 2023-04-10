#include "tiny_mesh_viewer/shader/shader.h"

#include <memory>
#include <stdexcept>
#include <string>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/shader/gouraud.h"
#include "tiny_mesh_viewer/shader/phong.h"

namespace tiny_mesh_viewer::shader {

std::shared_ptr<Shader> Shader::FromYAML(const YAML::Node& yaml) {
  auto&& type = yaml["type"].as<std::string>();
  if (type == "Phong") {
    return Phong::FromYAML(yaml);
  } else if (type == "Gouraud") {
    return Gouraud::FromYAML(yaml);
  } else {
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(),
        /*what=*/"Unknown shader type: " + type);
  }
  return nullptr;
}

}  // namespace tiny_mesh_viewer::shader
