#ifndef TINY_MESH_VIEWER_SCENE_CAMERA_H_
#define TINY_MESH_VIEWER_SCENE_CAMERA_H_

#include <memory>

#include "boost/signals2.hpp"
#include "glm/glm.hpp"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/scene/light/point_light.h"
#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::ui {
class Window;
}  // namespace tiny_mesh_viewer::ui

namespace tiny_mesh_viewer::scene {

class Camera {
 public:
  explicit Camera(const glm::vec3& position = kDefaultPosition,
                  const glm::vec3& look_at = kDefaultLookAt,
                  const glm::vec3& up = kDefaultUp,
                  const float fov = kDefaultFOV,
                  const float z_near = kDefaultZNear,
                  const float z_far = kDefaultZFar,
                  const float translation_speed = kDefaultTranslationSpeed,
                  const float yaw_speed = kDefaultYawSpeed,
                  const float pitch_speed = kDefaultPitchSpeed);

  void ConnectShader(shader::Shader& shader, ui::Window& window);
  void ConnectPointLight(PointLight& point_light);
  void TrackMovement(ui::Window& window, const float delta_time);
  void TrackRotation(ui::Window& window, double x, double y);

  glm::mat4 Projection(const float aspect) const;

  glm::vec3 position() const;
  void set_position(const glm::vec3& position);
  glm::vec3 look_at() const;
  void set_look_at(const glm::vec3& look_at);
  glm::vec3 up() const;
  void set_up(const glm::vec3& up);
  float fov() const;
  void set_fov(const float fov);
  float z_near() const;
  void set_z_near(const float z_near);
  float z_far() const;
  void set_z_far(const float z_far);
  float translation_speed() const;
  void set_translation_speed(const float translation_speed);
  float yaw_speed() const;
  void set_yaw_speed(const float yaw_speed);
  float pitch_speed() const;
  void set_pitch_speed(const float pitch_speed);

  static std::shared_ptr<Camera> FromYAML(const YAML::Node& yaml);

  boost::signals2::signal<void(const Camera& camera)> changed;

 private:
  glm::vec3 look_at_;
  glm::vec3 position_;
  glm::vec3 up_;
  float fov_, z_far_, z_near_;
  float translation_speed_, yaw_speed_, pitch_speed_;

  glm::vec2 last_cursor_pos_; /**< used for tracking mouse movement */

  static constexpr glm::vec3 kDefaultPosition = glm::vec3(2.0, 0.0, 0.0);
  static constexpr glm::vec3 kDefaultLookAt = glm::vec3(0.0, 0.0, 0.0);
  static constexpr glm::vec3 kDefaultUp = glm::vec3(0.0, 1.0, 0.0);
  static constexpr float kDefaultFOV = 45.0;
  static constexpr float kDefaultZNear = 0.1;
  static constexpr float kDefaultZFar = 100.0;
  static constexpr float kDefaultTranslationSpeed = 1.0;
  static constexpr float kDefaultYawSpeed = 1e-3;
  static constexpr float kDefaultPitchSpeed = 1e-3;
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_CAMERA_H_
