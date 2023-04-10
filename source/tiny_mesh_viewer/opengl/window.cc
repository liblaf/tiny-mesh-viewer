#include "tiny_mesh_viewer/opengl/window.h"

#include <memory>
#include <string_view>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace tiny_mesh_viewer::opengl {

Window::Window(const int width, const int height, const std::string_view title,
               GLFWmonitor* monitor, GLFWwindow* share) {
  Hint(/*hint=*/GLFW_CONTEXT_VERSION_MAJOR,
       /*value=*/kContextVersionMajor);
  Hint(/*hint=*/GLFW_CONTEXT_VERSION_MINOR,
       /*value=*/kContextVersionMinor);
  Hint(/*hint=*/GLFW_OPENGL_PROFILE,
       /*value=*/kOpenGLProfile);
#ifdef __APPLE__
  Hint(/*hint=*/GLFW_OPENGL_FORWARD_COMPAT, /*value=*/GL_TRUE);
#endif

  this->window_ = glfwCreateWindow(width, height, title.data(), monitor, share);
}

Window::~Window() { glfwDestroyWindow(this->window_); }

glm::ivec2 Window::FramebufferSize() const {
  int width, height;
  glfwGetFramebufferSize(this->window_, &width, &height);
  return glm::ivec2(width, height);
}

int Window::GetKey(int key) { return glfwGetKey(this->window_, key); }

void Window::MakeContextCurrent() { glfwMakeContextCurrent(this->window_); }

int Window::ShouldClose() { return glfwWindowShouldClose(this->window_); }

GLFWcursorposfun Window::SetCursorPosCallback(GLFWcursorposfun callback) {
  return glfwSetCursorPosCallback(this->window_, callback);
}

GLFWframebuffersizefun Window::SetFramebufferSizeCallback(
    GLFWframebuffersizefun callback) {
  return glfwSetFramebufferSizeCallback(this->window_, callback);
}

void Window::SetTitle(const std::string_view title) {
  glfwSetWindowTitle(this->window_, title.data());
}

void Window::SetWindowUserPointer(void* pointer) {
  glfwSetWindowUserPointer(this->window_, pointer);
}

void Window::SwapBuffers() { glfwSwapBuffers(this->window_); }

void Window::Hint(const int hint, const int value) {
  glfwWindowHint(hint, value);
}

}  // namespace tiny_mesh_viewer::opengl
