#ifndef TINY_MESH_VIEWER_OPENGL_APP_H_
#define TINY_MESH_VIEWER_OPENGL_APP_H_

#include "glad/glad.h"

namespace tiny_mesh_viewer::opengl {

class App {
 public:
  explicit App();
  ~App();

  void Enable(GLenum cap);
  void Init();
  void LoadGLLoader(GLADloadproc proc);
  void Terminate();

  static double GetTime();
  static void PollEvents();
};

}  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_APP_H_
