#include "tiny_mesh_viewer/scene/object/object.h"

#include <memory>
#include <string>
#include <string_view>

#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/common/config.h"
#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/scene/object/tri_mesh.h"

namespace tiny_mesh_viewer::scene {

Object::Object(const glm::vec3& position, const glm::vec3& rotation,
               const glm::vec3& translation_speed,
               const glm::vec3& rotation_speed) {
  this->set_position(position);
  this->set_rotation(rotation);
  this->set_translation_speed(translation_speed);
  this->set_rotation_speed(rotation_speed);
}

void Object::Draw() {
  if (!this->shader_) return;
  auto with = common::WithUse(this->shader());
  this->shader().UniformMat4(
      /*name=*/"model_view",
      /*value=*/this->ModelView());
  this->shader().UniformMat4(/*name=*/"normal_matrix",
                             /*value=*/this->NormalMatrix());
}

void Object::Load() {}

void Object::Update(const float delta_time) {
  this->set_position(this->position() + this->translation_speed() * delta_time);
  this->set_rotation(this->rotation() + this->rotation_speed() * delta_time);
}

glm::mat4 Object::ModelView() const {
  glm::mat4 model_view =
      glm::translate(glm::identity<glm::mat4>(), this->position());
  auto&& rotation = glm::radians(this->rotation());
  model_view =
      model_view * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
  return model_view;
}

glm::mat4 Object::NormalMatrix() const {
  return glm::inverseTranspose(this->ModelView());
}

glm::vec3 Object::position() const { return this->position_; }

void Object::set_position(const glm::vec3& position) {
  this->position_ = position;
}

glm::vec3 Object::rotation() const { return this->rotation_; }

void Object::set_rotation(const glm::vec3& rotation) {
  this->rotation_ = rotation;
}

glm::vec3 Object::translation_speed() const { return this->translation_speed_; }

void Object::set_translation_speed(const glm::vec3& translation_speed) {
  this->translation_speed_ = translation_speed;
}

glm::vec3 Object::rotation_speed() const { return this->rotation_speed_; }

void Object::set_rotation_speed(const glm::vec3& rotation_speed) {
  this->rotation_speed_ = rotation_speed;
}

shader::Shader& Object::shader() { return *(this->shader_); }

void Object::set_shader(std::shared_ptr<shader::Shader> shader) {
  this->shader_ = shader;
}

std::string_view Object::shader_id() const { return this->shader_id_; }

void Object::set_shader_id(const std::string_view shader_id) {
  this->shader_id_ = shader_id;
}

std::shared_ptr<Object> Object::FromYAML(const YAML::Node& yaml) {
  auto&& type = yaml["type"].as<std::string>();
  std::shared_ptr<Object> object = nullptr;
  if (type == "TriMesh") {
    object = TriMesh::FromYAML(yaml);
  } else {
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(),
        /*what=*/"Unknown object type: " + type);
  }
  object->set_shader_id(yaml["shader_id"].as<std::string>());
  object->set_position(
      common::Config::AsVec3(yaml["position"], /*fallback=*/kDefaultPosition));
  object->set_rotation(
      common::Config::AsVec3(yaml["rotation"], /*fallback=*/kDefaultRotation));
  object->set_translation_speed(
      common::Config::AsVec3(yaml["translation_speed"],
                             /*fallback=*/kDefaultTranslationSpeed));
  object->set_rotation_speed(
      common::Config::AsVec3(yaml["rotation_speed"],
                             /*fallback=*/kDefaultRotationSpeed));
  return object;
}

}  // namespace tiny_mesh_viewer::scene
