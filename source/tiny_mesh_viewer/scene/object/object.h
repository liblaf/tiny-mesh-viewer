#ifndef TINY_MESH_VIEWER_SCENE_OBJECT_OBJECT_H_
#define TINY_MESH_VIEWER_SCENE_OBJECT_OBJECT_H_

#include <memory>
#include <string>
#include <string_view>

#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::scene {

class Object {
 public:
  Object(const glm::vec3& position = kDefaultPosition,
         const glm::vec3& rotation = kDefaultRotation,
         const glm::vec3& translation_speed = kDefaultTranslationSpeed,
         const glm::vec3& rotation_speed = kDefaultRotationSpeed);
  virtual ~Object() = default;

  virtual void Draw();

  /** Create OpenGL object and copy data to buffers
   */
  virtual void Load();

  /** Update position & rotation
   */
  void Update(const float delta_time);

  glm::mat4 ModelView() const;
  glm::mat4 NormalMatrix() const;

  glm::vec3 position() const;
  void set_position(const glm::vec3& position);
  glm::vec3 rotation() const;
  void set_rotation(const glm::vec3& rotation);
  glm::vec3 translation_speed() const;
  void set_translation_speed(const glm::vec3& translation_speed);
  glm::vec3 rotation_speed() const;
  void set_rotation_speed(const glm::vec3& rotation_speed);
  shader::Shader& shader();
  void set_shader(std::shared_ptr<shader::Shader> shader);
  std::string_view shader_id() const;
  void set_shader_id(const std::string_view shader_id);

  static std::shared_ptr<Object> FromYAML(const YAML::Node& yaml);

 protected:
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 translation_speed_;
  glm::vec3 rotation_speed_;

  std::shared_ptr<shader::Shader> shader_;
  std::string shader_id_;

  static constexpr glm::vec3 kDefaultPosition = glm::vec3(0.0, 0.0, 0.0);
  static constexpr glm::vec3 kDefaultRotation = glm::vec3(0.0, 0.0, 0.0);
  static constexpr glm::vec3 kDefaultTranslationSpeed =
      glm::vec3(0.0, 0.0, 0.0);
  static constexpr glm::vec3 kDefaultRotationSpeed = glm::vec3(0.0, 0.0, 0.0);
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_OBJECT_OBJECT_H_
