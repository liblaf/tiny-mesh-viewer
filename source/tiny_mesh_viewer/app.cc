#include "tiny_mesh_viewer/app.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/scene/camera.h"
#include "tiny_mesh_viewer/scene/light/ambient_light.h"
#include "tiny_mesh_viewer/scene/light/point_light.h"
#include "tiny_mesh_viewer/scene/object/object.h"
#include "tiny_mesh_viewer/scene/scene.h"
#include "tiny_mesh_viewer/ui/canvas.h"
#include "tiny_mesh_viewer/ui/window.h"

namespace tiny_mesh_viewer {

App::App(const YAML::Node& yaml) {
  auto canvas = ui::Canvas::FromYAML(yaml["canvas"]);
  this->window_ = std::make_unique<ui::Window>(canvas);

  this->LoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  this->Enable(/*cap=*/GL_DEPTH_TEST);

  this->scene_ = scene::Scene::FromYAML(yaml["scene"]);
  this->window().canvas().set_scene(this->scene_);

  if (yaml["shaders"]) {
    std::for_each(yaml["shaders"].begin(), yaml["shaders"].end(),
                  [&shaders = this->shaders_, &scene = this->scene(),
                   &window = this->window()](const YAML::Node& yaml) -> void {
                    auto shader = shader::Shader::FromYAML(yaml);
                    scene.ambient_light().ConnectShader(*shader);
                    // scene.camera().ConnectPointLight(scene.point_light());
                    scene.camera().ConnectShader(*shader, window);
                    scene.point_light().ConnectShader(*shader);
                    window.ConnectShader(*shader, scene.camera());
                    shaders.insert({yaml["id"].as<std::string>(), shader});
                  });
  }

  std::for_each(
      this->scene().objects().begin(), this->scene().objects().end(),
      [&shaders =
           this->shaders_](std::shared_ptr<scene::Object> object) -> void {
        object->Load();
        object->set_shader(shaders.at(std::string(object->shader_id())));
      });

  this->window().cursor_moved.connect(
      [&camera = this->scene().camera()](ui::Window& window, double x,
                                         double y) -> void {
        camera.TrackRotation(window, x, y);
      });

  this->window().new_frame.connect(
      [&camera = this->scene().camera()](ui::Window& window,
                                         double delta_time) -> void {
        camera.TrackMovement(window, delta_time);
      });
  this->window().new_frame.connect([&objects = this->scene().objects()](
                                       ui::Window& window,
                                       double delta_time) -> void {
    std::for_each(objects.begin(), objects.end(),
                  [&delta_time](std::shared_ptr<scene::Object> object) -> void {
                    object->Update(delta_time);
                  });
  });

  this->scene().camera().changed(this->scene().camera());
  this->scene().ambient_light().changed(this->scene().ambient_light());
  this->scene().point_light().changed(this->scene().point_light());
}

void App::Run() { this->window().Run(); }

scene::Scene& App::scene() { return *(this->scene_); }

ui::Window& App::window() { return *(this->window_); }

}  // namespace tiny_mesh_viewer
