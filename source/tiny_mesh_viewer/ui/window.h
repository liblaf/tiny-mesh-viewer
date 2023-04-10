#ifndef TINY_MESH_VIEWER_UI_WINDOW_H_
#define TINY_MESH_VIEWER_UI_WINDOW_H_

#include <memory>
#include <string>
#include <string_view>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "boost/signals2.hpp"
#include "canvas.h"

#include "tiny_mesh_viewer/opengl/window.h"
#include "tiny_mesh_viewer/scene/camera.h"

namespace tiny_mesh_viewer::ui {

class Window : public tiny_mesh_viewer::opengl::Window {
 public:
  explicit Window(const int width = 800, const int height = 600,
                  const std::string_view title = "Tiny Mesh Viewer",
                  GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
  explicit Window(std::shared_ptr<Canvas> canvas);

  void Run();

  void ConnectShader(shader::Shader& shader, scene::Camera& camera);

  Canvas& canvas();

  boost::signals2::signal<void(Window& window, int width, int height)>
      framebuffer_size_changed;
  boost::signals2::signal<void(Window& window, double frame_duration)>
      new_frame;
  boost::signals2::signal<void(Window& window, double x, double y)>
      cursor_moved;

 protected:
  void Init();

 private:
  std::shared_ptr<Canvas> canvas_;

  double last_frame_time_ = 0.0; /**< used to compute FPS */
};

}  // namespace tiny_mesh_viewer::ui

#endif  // TINY_MESH_VIEWER_UI_WINDOW_H_
