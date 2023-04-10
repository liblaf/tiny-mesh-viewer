#ifndef TINY_MESH_VIEWER_OPENGL_WINDOW_H_
#define TINY_MESH_VIEWER_OPENGL_WINDOW_H_

#include <memory>
#include <string_view>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace tiny_mesh_viewer::opengl {

class Window {
 public:
  explicit Window(const int width = 800, const int height = 600,
                  const std::string_view title = "Tiny Mesh Viewer",
                  GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
  ~Window();

  glm::ivec2 FramebufferSize() const;
  int GetKey(int key);
  void MakeContextCurrent();
  GLFWcursorposfun SetCursorPosCallback(GLFWcursorposfun callback);
  GLFWframebuffersizefun SetFramebufferSizeCallback(
      GLFWframebuffersizefun callback);
  void SetTitle(const std::string_view title);
  void SetWindowUserPointer(void* pointer);
  int ShouldClose();
  void SwapBuffers();

  static void Hint(const int hint, const int value);

 private:
  GLFWwindow* window_;

  static constexpr int kContextVersionMajor = 3;
  static constexpr int kContextVersionMinor = 3;
  static constexpr int kOpenGLProfile = GLFW_OPENGL_CORE_PROFILE;
};

}  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_WINDOW_H_
