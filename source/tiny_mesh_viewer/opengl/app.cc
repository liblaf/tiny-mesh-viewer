#include "tiny_mesh_viewer/opengl/app.h"

#include <stdexcept>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"

namespace tiny_mesh_viewer::opengl {

App::App() { this->Init(); }

App::~App() { this->Terminate(); }

void App::Enable(GLenum cap) { glEnable(cap); }

void App::Init() {
  int ret = glfwInit();
  if (ret != GLFW_TRUE) {
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(), /*what=*/"glfwInit()");
  }
}

void App::LoadGLLoader(GLADloadproc proc) {
  if (!gladLoadGLLoader(proc)) {
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(), /*what=*/"gladLoadGLLoader()");
  }
}

void App::Terminate() { glfwTerminate(); }

double App::GetTime() { return glfwGetTime(); }

void App::PollEvents() { glfwPollEvents(); }

}  // namespace tiny_mesh_viewer::opengl
