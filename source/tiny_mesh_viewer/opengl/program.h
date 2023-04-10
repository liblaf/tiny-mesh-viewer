#ifndef TINY_MESH_VIEWER_OPENGL_PROGRAM_H_
#define TINY_MESH_VIEWER_OPENGL_PROGRAM_H_

#include <string_view>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "tiny_mesh_viewer/opengl/shader.h"

namespace tiny_mesh_viewer::opengl {

class Program {
 public:
  explicit Program();
  ~Program();

  template <GLenum shader_type>
  void AttachShader(const Shader<shader_type>& shader) {
    glAttachShader(/*program=*/this->id_, /*shader=*/shader.id());
  }

  void Link();
  void Use();
  void Unuse();

  void UniformFloat(const std::string_view name, const float value);
  void UniformMat4(const std::string_view name, const glm::mat4& value);
  void UniformVec3(const std::string_view name, const glm::vec3& value);
  float GetUniformFloat(const std::string_view name) const;
  glm::mat4 GetUniformMat4(const std::string_view name) const;
  glm::vec3 GetUniformVec3(const std::string_view name) const;

 private:
  GLuint id_;
};

}  // namespace tiny_mesh_viewer::opengl

#endif  // TINY_MESH_VIEWER_OPENGL_PROGRAM_H_
