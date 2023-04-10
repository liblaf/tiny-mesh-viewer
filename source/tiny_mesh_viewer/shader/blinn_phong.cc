#include "tiny_mesh_viewer/shader/blinn_phong.h"

#include <memory>

#include "cmrc/cmrc.hpp"

#include "tiny_mesh_viewer/common/resource.h"

namespace tiny_mesh_viewer::shader {

BlinnPhong::BlinnPhong(const std::filesystem::path& vertex_shader_filepath,
                       const std::filesystem::path& fragment_shader_filepath) {
  auto vertex_shader = std::make_unique<opengl::VertexShader>();
  {
    cmrc::file file = common::Resource::Open(vertex_shader_filepath);
    const char* source = file.begin();
    vertex_shader->Source(/*count=*/1, /*string=*/&source);
    vertex_shader->Compile();
  }
  auto fragment_shader = std::make_unique<opengl::FragmentShader>();
  {
    cmrc::file file = common::Resource::Open(fragment_shader_filepath);
    const char* source = file.begin();
    fragment_shader->Source(/*count=*/1, /*string=*/&source);
    fragment_shader->Compile();
  }
  this->AttachShader(*vertex_shader);
  this->AttachShader(*fragment_shader);
  this->Link();
}

void BlinnPhong::LoadYAML(const YAML::Node& yaml) {
  this->UniformFloat(
      /*name=*/"ambient_reflection",
      /*value=*/yaml["ambient_reflection"].as<float>(
          /*fallback=*/kDefaultAmbientReflection));
  this->UniformFloat(
      /*name=*/"diffuse_reflection",
      /*value=*/yaml["diffuse_reflection"].as<float>(
          /*fallback=*/kDefaultDiffuseReflection));
  this->UniformFloat(
      /*name=*/"specular_reflection",
      /*value=*/yaml["specular_reflection"].as<float>(
          /*fallback=*/kDefaultSpecularReflection));
  this->UniformFloat(
      /*name=*/"shininess",
      /*value=*/yaml["shininess"].as<float>(/*fallback=*/kDefaultShininess));
}

}  // namespace tiny_mesh_viewer::shader
