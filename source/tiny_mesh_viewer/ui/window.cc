#include "tiny_mesh_viewer/ui/window.h"

#include <memory>
#include <string_view>

#include "GLFW/glfw3.h"
#include "dbg.h"
#include "fmt/core.h"
#include "spdlog/spdlog.h"

#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/opengl/app.h"
#include "tiny_mesh_viewer/opengl/window.h"
#include "tiny_mesh_viewer/ui/canvas.h"

namespace tiny_mesh_viewer::ui {

Window::Window(std::shared_ptr<Canvas> canvas) {
  this->canvas_ = canvas;
  this->Init();
}

Window::Window(const int width, const int height, const std::string_view title,
               GLFWmonitor* monitor, GLFWwindow* share)
    : tiny_mesh_viewer::opengl::Window(width, height, title, monitor, share) {
  this->canvas_ = std::make_shared<Canvas>();
  this->Init();
}

void Window::Run() {
  while (!this->ShouldClose()) {
    double current_time = opengl::App::GetTime();
    double delta_time = current_time - this->last_frame_time_;
    this->last_frame_time_ = current_time;
    this->new_frame(*this, delta_time);
    this->canvas().Draw();
    this->SwapBuffers();
    opengl::App::PollEvents();
  }
}

void Window::ConnectShader(shader::Shader& shader, scene::Camera& camera) {
  this->framebuffer_size_changed.connect(
      [&shader, &camera](Window& window, int width, int height) -> void {
        auto with = common::WithUse(shader);
        auto aspect = static_cast<float>(width) / static_cast<float>(height);
        shader.UniformMat4(/*name*/ "projection",
                           /*value=*/camera.Projection(aspect));
      });
}

Canvas& Window::canvas() { return *(this->canvas_); }

void Window::Init() {
  this->MakeContextCurrent();
  this->SetWindowUserPointer(this);

  this->SetCursorPosCallback(
      [](GLFWwindow* window, double x, double y) -> void {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        self->cursor_moved(*self, x, y);
      });

  this->SetFramebufferSizeCallback(
      [](GLFWwindow* window, int width, int height) -> void {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        glViewport(/*x=*/0, /*y=*/0, width, height);
        self->framebuffer_size_changed(*self, width, height);
      });

  this->new_frame.connect([](Window& window, double frame_duration) -> void {
    static int frames = 0;
    static float duration = 0.0;
    ++frames;
    duration += frame_duration;
    if (duration > 1.0) {
      window.SetTitle(
          fmt::format(/*fmt=*/"Tiny Mesh Viewer ({} FPS)", frames / duration));
      duration = 0.0;
      frames = 0;
    }
  });

#ifdef DEBUG_WINDOW
  this->framebuffer_size_changed.connect(
      [](Window& window, int width, int height) -> void {
        INFO("Framebuffer size changed: {}x{}", width, height);
      });
#endif  // DEBUG_WINDOW
}

}  // namespace tiny_mesh_viewer::ui
