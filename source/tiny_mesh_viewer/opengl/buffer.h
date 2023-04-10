#ifndef TINY_MESH_VIEWER_OPENGL_BUFFER_H_
#define TINY_MESH_VIEWER_OPENGL_BUFFER_H_

#include "glad/glad.h"

#include "tiny_mesh_viewer/common/with.h"

namespace tiny_mesh_viewer::opengl {

template <GLenum target>
class Buffer {
 public:
  explicit Buffer() { glGenBuffers(/*n=*/1, /*buffers=*/&(this->id_)); }

  ~Buffer() { glDeleteBuffers(/*n=*/1, /*buffers=*/&(this->id_)); }

  void Bind() { glBindBuffer(target, /*buffer=*/this->id_); }

  void Unbind() { glBindBuffer(target, /*buffer*/ this->id_); }

  void Data(const GLsizeiptr size, const void* data,
            GLenum usage = GL_STATIC_DRAW) {
    glBufferData(target, size, data, usage);
  }

 protected:
  GLuint id() const { return this->id_; }

 private:
  GLuint id_ = 0;
};

using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
using ElementArrayBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;

}  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_BUFFER_H_
