#include "tiny_mesh_viewer/opengl/program.h"

#include <stdexcept>
#include <string>
#include <string_view>

#include "glad/glad.h"
#include "dbg.h"
#include "glm/gtx/io.hpp"

#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/opengl/shader.h"

namespace tiny_mesh_viewer::opengl {

Program::Program() { this->id_ = glCreateProgram(); }

Program::~Program() { glDeleteProgram(/*program=*/this->id_); }

void Program::Link() {
  glLinkProgram(/*program=*/this->id_);
  int success;
  glGetProgramiv(/*program=*/this->id_, /*pname=*/GL_LINK_STATUS,
                 /*params=*/&success);
  if (!success) {
    static constexpr int kMaxLength = 1024;
    char info_log[kMaxLength];
    glGetProgramInfoLog(/*program=*/this->id_, kMaxLength, /*length=*/nullptr,
                        info_log);
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(),
        /*what=*/"glLinkProgram(): " + std::string(info_log));
  }
}

void Program::Use() { glUseProgram(/*program=*/this->id_); }

void Program::Unuse() { glUseProgram(/*program=*/0); }

void Program::UniformFloat(const std::string_view name, const float value) {
#ifdef DEBUG_UNIFORM
  dbg(name, value);
#endif
  glUniform1f(glGetUniformLocation(/*program=*/this->id_, name.data()),
              /*v0=*/value);
}

void Program::UniformMat4(const std::string_view name, const glm::mat4& value) {
#ifdef DEBUG_UNIFORM
  dbg(name, value);
#endif
  glUniformMatrix4fv(glGetUniformLocation(/*program=*/this->id_, name.data()),
                     /*count=*/1, /*transpose=*/GL_FALSE, &value[0][0]);
}

void Program::UniformVec3(const std::string_view name, const glm::vec3& value) {
#ifdef DEBUG_UNIFORM
  dbg(name, value);
#endif
  glUniform3fv(glGetUniformLocation(/*program=*/this->id_, name.data()),
               /*count=*/1, &value[0]);
}

float Program::GetUniformFloat(const std::string_view name) const {
  float value;
  glGetUniformfv(/*program=*/this->id_,
                 glGetUniformLocation(/*program=*/this->id_, name.data()),
                 /*params=*/&value);
  return value;
}

glm::mat4 Program::GetUniformMat4(const std::string_view name) const {
  glm::mat4 value;
  glGetUniformfv(/*program=*/this->id_,
                 glGetUniformLocation(/*program=*/this->id_, name.data()),
                 /*params=*/&value[0][0]);
  return value;
}

glm::vec3 Program::GetUniformVec3(const std::string_view name) const {
  glm::vec3 value;
  glGetUniformfv(/*program=*/this->id_,
                 glGetUniformLocation(/*program=*/this->id_, name.data()),
                 /*params=*/&value[0]);
  return value;
}

}  // namespace tiny_mesh_viewer::opengl
