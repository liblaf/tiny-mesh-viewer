#ifndef TINY_MESH_VIEWER_OPENGL_SHADER_H_
#define TINY_MESH_VIEWER_OPENGL_SHADER_H_

#include <stdexcept>
#include <string>

#include "glad/glad.h"

#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"

namespace tiny_mesh_viewer::opengl {

template <GLenum shader_type>
class Shader {
 public:
  explicit Shader() { this->id_ = glCreateShader(shader_type); }

  ~Shader() { glDeleteShader(/*shader=*/this->id_); }

  void Compile() {
    glCompileShader(/*shader=*/this->id_);
    int success;
    glGetShaderiv(/*shader=*/this->id_, /*pname=*/GL_COMPILE_STATUS,
                  /*params=*/&success);
    if (!success) {
      static constexpr int kMaxLength = 1024;
      char info_log[kMaxLength];
      glGetShaderInfoLog(/*shader=*/this->id_, kMaxLength,
                         /*length=*/nullptr, info_log);
      throw common::Exception<std::runtime_error>(
          /*loc=*/common::source_loc::current(),
          /*what=*/"glCompileShader(): " + std::string(info_log));
    }
  }

  void Source(GLsizei count, const GLchar** string,
              const GLint* length = nullptr) {
    glShaderSource(/*shader=*/this->id_, count, string, length);
  }

  GLuint id() const { return this->id_; }

 private:
  GLuint id_ = 0;
};

using VertexShader = Shader<GL_VERTEX_SHADER>;
using FragmentShader = Shader<GL_FRAGMENT_SHADER>;

};  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_SHADER_H_
