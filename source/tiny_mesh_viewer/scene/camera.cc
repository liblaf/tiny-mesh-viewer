#include "tiny_mesh_viewer/scene/camera.h"

#include <algorithm>
#include <memory>

#include "dbg.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/io.hpp"
#include "glm/gtx/string_cast.hpp"

#include "tiny_mesh_viewer/common/config.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/math.h"
#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/ui/window.h"

namespace tiny_mesh_viewer::scene {

Camera::Camera(const glm::vec3& position, const glm::vec3& look_at,
               const glm::vec3& up, const float fov, const float z_near,
               const float z_far, const float translation_speed,
               const float yaw_speed, const float pitch_speed) {
  this->set_position(position);
  this->set_look_at(look_at);
  this->set_up(up);
  this->set_fov(fov);
  this->set_z_near(z_near);
  this->set_z_far(z_far);
  this->set_translation_speed(translation_speed);
  this->set_yaw_speed(yaw_speed);
  this->set_pitch_speed(pitch_speed);

#ifdef DEBUG_CAMERA
  this->changed.connect([](const Camera& camera) -> void {
    INFO("Camera changed:");
    INFO("  position: {}", glm::to_string(camera.position()));
    INFO("  look_at: {}", glm::to_string(camera.look_at()));
    INFO("  up: {}", glm::to_string(camera.up()));
    INFO("  fov: {}", camera.fov());
    INFO("  z_near: {}", camera.z_near());
    INFO("  z_far: {}", camera.z_far());
    INFO("  translation_speed: {}", camera.translation_speed());
    INFO("  yaw_speed: {}", camera.yaw_speed());
    INFO("  pitch_speed: {}", camera.pitch_speed());
  });
#endif  // DEBUG_CAMERA
}

void Camera::ConnectShader(shader::Shader& shader, ui::Window& window) {
  this->changed.connect([&shader, &window](const Camera& camera) -> void {
    auto with = common::WithUse(shader);
    glm::ivec2 size = window.FramebufferSize();
    float aspect = static_cast<float>(size.x) / static_cast<float>(size.y);
    auto&& projection = camera.Projection(aspect);
    shader.UniformMat4(/*name=*/"projection",
                       /*value=*/projection);
    shader.UniformVec3(/*name=*/"camera_position", /*value=*/camera.position());
  });
}

void Camera::ConnectPointLight(PointLight& point_light) {
  this->changed.connect([&point_light](const Camera& camera) -> void {
    point_light.set_position(camera.position());
  });
}

void Camera::TrackMovement(ui::Window& window, const float delta_time) {
  glm::vec3 front = glm::normalize(this->look_at() - this->position());
  glm::vec3 right = glm::normalize(glm::cross(front, this->up()));
  front = glm::normalize(glm::cross(this->up(), right));
  glm::vec3 position_change = glm::vec3(0.0);
  if (window.GetKey(GLFW_KEY_A) == GLFW_PRESS) {
    position_change -= this->translation_speed() * delta_time * right;
  }
  if (window.GetKey(GLFW_KEY_S) == GLFW_PRESS) {
    position_change -= this->translation_speed() * delta_time * front;
  }
  if (window.GetKey(GLFW_KEY_D) == GLFW_PRESS) {
    position_change += this->translation_speed() * delta_time * right;
  }
  if (window.GetKey(GLFW_KEY_W) == GLFW_PRESS) {
    position_change += this->translation_speed() * delta_time * front;
  }
  if (window.GetKey(GLFW_KEY_E) == GLFW_PRESS) {
    position_change += this->translation_speed() * delta_time * this->up();
  }
  if (window.GetKey(GLFW_KEY_Q) == GLFW_PRESS) {
    position_change -= this->translation_speed() * delta_time * this->up();
  }
  this->set_position(this->position() + position_change);
  this->set_look_at(this->look_at() + position_change);
}

void Camera::TrackRotation(ui::Window& window, double x, double y) {
  static constexpr float kEps = 1e-6;
  y = -y;
  if (glm::epsilonEqual(glm::length(this->last_cursor_pos_), 0.0f, kEps)) {
    this->last_cursor_pos_ = {x, y};
  }

  if (window.GetKey(GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
      window.GetKey(GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
    auto&& front = glm::normalize(this->look_at() - this->position());
    auto&& euler = common::math::VectorToEuler(front);
    float yaw = euler[0];
    float pitch = euler[1];
    yaw -= this->yaw_speed_ * (x - this->last_cursor_pos_.x);
    pitch += this->pitch_speed_ * (y - this->last_cursor_pos_.y);
    pitch = glm::clamp(pitch, /*minVal=*/glm::radians(/*degrees=*/-89.0f),
                       /*maxVal=*/glm::radians(/*degrees=*/+89.0f));
    front = common::math::EulerToVector(glm::vec2(yaw, pitch));
    this->set_look_at(this->position() + front);
  }
  this->last_cursor_pos_ = {x, y};
}

glm::mat4 Camera::Projection(const float aspect) const {
  return glm::perspective(/*fovy=*/glm::radians(/*degrees=*/this->fov()),
                          aspect, this->z_near(), this->z_far()) *
         glm::lookAt(this->position(), this->look_at(), this->up());
}

glm::vec3 Camera::position() const { return this->position_; }

void Camera::set_position(const glm::vec3& position) {
  this->position_ = position;
  this->changed(*this);
}

glm::vec3 Camera::look_at() const { return this->look_at_; }

void Camera::set_look_at(const glm::vec3& look_at) {
  this->look_at_ = look_at;
  this->changed(*this);
}

glm::vec3 Camera::up() const { return this->up_; }

void Camera::set_up(const glm::vec3& up) {
  this->up_ = up;
  this->changed(*this);
}

float Camera::fov() const { return this->fov_; }

void Camera::set_fov(const float fov) {
  this->fov_ = fov;
  this->changed(*this);
}

float Camera::z_near() const { return this->z_near_; }

void Camera::set_z_near(const float z_near) {
  this->z_near_ = z_near;
  this->changed(*this);
}

float Camera::z_far() const { return this->z_far_; }

void Camera::set_z_far(const float z_far) {
  this->z_far_ = z_far;
  this->changed(*this);
}

float Camera::translation_speed() const { return this->translation_speed_; }

void Camera::set_translation_speed(const float translation_speed) {
  this->translation_speed_ = translation_speed;
}

float Camera::yaw_speed() const { return this->yaw_speed_; }

void Camera::set_yaw_speed(const float yaw_speed) {
  this->yaw_speed_ = yaw_speed;
}

float Camera::pitch_speed() const { return this->pitch_speed_; }

void Camera::set_pitch_speed(const float pitch_speed) {
  this->pitch_speed_ = pitch_speed;
}

std::shared_ptr<Camera> Camera::FromYAML(const YAML::Node& yaml) {
  if (!yaml.IsDefined()) return std::make_shared<Camera>();
  return std::make_shared<Camera>(
      /*position=*/common::Config::AsVec3(yaml["position"],
                                          /*fallback=*/kDefaultPosition),
      /*look_at=*/
      common::Config::AsVec3(yaml["look_at"], /*fallback=*/kDefaultLookAt),
      /*up=*/common::Config::AsVec3(yaml["up"], /*fallback=*/kDefaultUp),
      /*fov=*/yaml["fov"].as<float>(/*fallback=*/kDefaultFOV),
      /*z_near=*/yaml["z_near"].as<float>(/*fallback=*/kDefaultZNear),
      /*z_far=*/yaml["z_far"].as<float>(/*fallback=*/kDefaultZFar),
      /*translation_speed=*/
      yaml["translation_speed"].as<float>(
          /*fallback=*/kDefaultTranslationSpeed),
      /*yaw_speed=*/yaml["yaw_speed"].as<float>(/*fallback=*/kDefaultYawSpeed),
      /*pitch_speed=*/
      yaml["pitch_speed"].as<float>(/*fallback=*/kDefaultPitchSpeed));
}

}  // namespace tiny_mesh_viewer::scene
