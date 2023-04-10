#include "tiny_mesh_viewer/scene/object/tri_mesh.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

#include "OpenMesh/Core/IO/MeshIO.hh"
#include "yaml-cpp/yaml.h"

#include "tiny_mesh_viewer/common/config.h"
#include "tiny_mesh_viewer/common/error.h"
#include "tiny_mesh_viewer/common/logging.h"
#include "tiny_mesh_viewer/common/with.h"
#include "tiny_mesh_viewer/opengl/buffer.h"
#include "tiny_mesh_viewer/opengl/vertex_array.h"
#include "tiny_mesh_viewer/shader/shader.h"

namespace tiny_mesh_viewer::scene {

void TriMesh::Draw() {
  if (!this->shader_) return;
  this->Object::Draw();
  auto with = common::WithUse(this->shader());
  this->shader().UniformVec3(/*name=*/"object_color", /*value=*/this->color());
  {
    auto with = common::WithBind(*(this->vertex_array_));
    glDrawElements(/*mode=*/GL_TRIANGLES, /*count=*/this->indices_.size(),
                   /*type=*/GL_UNSIGNED_INT, /*indices=*/nullptr);
  }
}

void TriMesh::Load() {
  this->array_buffer_ = std::make_unique<opengl::ArrayBuffer>();
  this->element_array_buffer_ = std::make_unique<opengl ::ElementArrayBuffer>();
  this->vertex_array_ = std::make_unique<opengl::VertexArray>();

  {
    auto with = common::WithBind(*(this->vertex_array_));
    {
      auto with = common::WithBind(*(this->array_buffer_));
      auto stride = sizeof(TriMesh::Vertex);
      this->array_buffer_->Data(
          /*size=*/this->vertices_.size() * stride,
          /*data=*/this->vertices_.data(),
          /*usage=*/GL_STATIC_DRAW);
      this->vertex_array_->VertexAttribPointer(
          /*index=*/0, /*size=*/3, /*type=*/GL_FLOAT,
          /*normalized=*/GL_FALSE,
          /*stride=*/stride,
          /*pointer=*/
          reinterpret_cast<void*>(offsetof(TriMesh::Vertex, position)));
      this->vertex_array_->EnableVertexAttribArray(/*index=*/0);
      this->vertex_array_->VertexAttribPointer(
          /*index=*/1, /*size=*/3, /*type=*/GL_FLOAT,
          /*normalized=*/GL_FALSE,
          /*stride=*/stride,
          /*pointer=*/
          reinterpret_cast<void*>(offsetof(TriMesh::Vertex, normal)));
      this->vertex_array_->EnableVertexAttribArray(/*index=*/1);
    }
    {
      auto with = common::WithBind(*(this->element_array_buffer_));
      this->element_array_buffer_->Data(
          /*size=*/this->indices_.size() * sizeof(int),
          /*data=*/this->indices_.data(), /*usage=*/GL_STATIC_DRAW);
    }
  }
}

glm::vec3 TriMesh::color() const { return this->color_; }

void TriMesh::set_color(const glm::vec3 color) { this->color_ = color; }

std::shared_ptr<TriMesh> TriMesh::FromYAML(const YAML::Node& yaml) {
  assert(yaml["type"].as<std::string>() == "TriMesh");
  bool flip_normals = yaml["flip_normals"].as<bool>(/*fallback=*/false);
  auto tri_mesh =
      TriMesh::Read(yaml["filepath"].as<std::string>(), flip_normals);
  tri_mesh->set_color(
      common::Config::AsVec3(yaml["color"], /*fallback=*/kDefaultColor));
  return tri_mesh;
}

std::shared_ptr<TriMesh> TriMesh::Read(const std::filesystem::path& filepath,
                                       const bool flip_normals) {
  TriMesh::MyMesh mesh;
  if (!OpenMesh::IO::read_mesh(mesh, /*filename=*/filepath)) {
    throw common::Exception<std::runtime_error>(
        /*loc=*/common::source_loc::current(),
        /*what=*/"read_mesh()");
  }
  mesh.request_face_normals();
  mesh.request_vertex_normals();
  mesh.update_normals();

  auto tri_mesh = std::make_shared<TriMesh>();
  std::transform(
      /*first=*/mesh.vertices_begin(),
      /*last=*/mesh.vertices_end(),
      /*result=*/std::back_inserter(tri_mesh->vertices_),
      /*unary_op=*/
      [&mesh, flip_normals](const TriMesh::MyMesh::VertexHandle vh) -> Vertex {
        return TriMesh::Vertex{
            .position = mesh.point(vh),
            .normal = flip_normals ? -mesh.normal(vh) : mesh.normal(vh),
        };
      });

  std::for_each(
      /*first=*/mesh.faces_begin(),
      /*last=*/mesh.faces_end(),
      /*f=*/
      [&mesh,
       &tri_mesh = *tri_mesh](const TriMesh::MyMesh::FaceHandle fh) -> void {
        std::for_each(
            /*first=*/mesh.fv_begin(fh),
            /*last=*/mesh.fv_end(fh),
            /*f=*/
            [&tri_mesh](const TriMesh::MyMesh::VertexHandle vh) -> void {
              tri_mesh.indices_.push_back(vh.idx());
            });
      });

  return tri_mesh;
}

}  // namespace tiny_mesh_viewer::scene
