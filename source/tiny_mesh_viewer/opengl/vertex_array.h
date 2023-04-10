#ifndef TINY_MESH_VIEWER_OPENGL_VERTEX_ARRAY_H_
#define TINY_MESH_VIEWER_OPENGL_VERTEX_ARRAY_H_

#include "glad/glad.h"

namespace tiny_mesh_viewer::opengl {

class VertexArray {
 public:
  explicit VertexArray();
  ~VertexArray();

  void Bind();
  void Unbind();

  void EnableVertexAttribArray(GLuint index);
  void VertexAttribPointer(GLuint index, GLint size, GLenum type,
                           GLboolean normalized, GLsizei stride,
                           const void* pointer);

 private:
  GLuint id_;
};

}  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_VERTEX_ARRAY_H_
