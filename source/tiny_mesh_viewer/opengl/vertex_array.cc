#include "tiny_mesh_viewer/opengl/vertex_array.h"

#include "glad/glad.h"

namespace tiny_mesh_viewer::opengl {

VertexArray::VertexArray() {
  glGenVertexArrays(/*n=*/1, /*arrays=*/&(this->id_));
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(/*n=*/1, /*arrays=*/&(this->id_));
}

void VertexArray::Bind() { glBindVertexArray(/*array=*/this->id_); }

void VertexArray::Unbind() { glBindVertexArray(/*array=*/0); }

void VertexArray::EnableVertexAttribArray(GLuint index) {
  glEnableVertexArrayAttrib(/*vaobj=*/this->id_, index);
}

void VertexArray::VertexAttribPointer(GLuint index, GLint size, GLenum type,
                                      GLboolean normalized, GLsizei stride,
                                      const void* pointer) {
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

}  // namespace tiny_mesh_viewer::opengl
