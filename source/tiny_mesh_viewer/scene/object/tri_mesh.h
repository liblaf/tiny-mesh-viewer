#ifndef TINY_MESH_VIEWER_SCENE_OBJECT_TRI_MESH_H_
#define TINY_MESH_VIEWER_SCENE_OBJECT_TRI_MESH_H_

#include <filesystem>
#include <memory>
#include <vector>

#include "OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh"
#include "boost/signals2.hpp"
#include "glm/glm.hpp"

#include "tiny_mesh_viewer/opengl/buffer.h"
#include "tiny_mesh_viewer/opengl/vertex_array.h"
#include "tiny_mesh_viewer/scene/object/object.h"

namespace tiny_mesh_viewer::scene {

class TriMesh : public Object {
 public:
  using MyMesh = OpenMesh::TriMesh_ArrayKernelT<>;

  struct Vertex {
    static_assert(sizeof(MyMesh::Point) == 3 * sizeof(float));
    static_assert(sizeof(MyMesh::Normal) == 3 * sizeof(float));
    MyMesh::Point position;
    MyMesh::Normal normal;
  };

  virtual ~TriMesh() = default;

  virtual void Draw() override;
  virtual void Load() override;

  glm::vec3 color() const;
  void set_color(const glm::vec3 color);

  static std::shared_ptr<TriMesh> FromYAML(const YAML::Node& yaml);
  static std::shared_ptr<TriMesh> Read(const std::filesystem::path& filepath,
                                       const bool flip_normals = false);

 private:
  std::vector<TriMesh::Vertex> vertices_;
  std::vector<unsigned> indices_;
  glm::vec3 color_ = kDefaultColor;

  std::unique_ptr<opengl::ArrayBuffer> array_buffer_;
  std::unique_ptr<opengl::ElementArrayBuffer> element_array_buffer_;
  std::unique_ptr<opengl::VertexArray> vertex_array_;

  static constexpr glm::vec3 kDefaultColor =
      glm::vec3(204.0 / 255.0, 102.0 / 255.0, 0.0);
};

}  // namespace tiny_mesh_viewer::scene

#endif  // TINY_MESH_VIEWER_SCENE_OBJECT_TRI_MESH_H_
