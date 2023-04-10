#ifndef TINY_MESH_VIEWER_COMMON_WITH_H_
#define TINY_MESH_VIEWER_COMMON_WITH_H_

namespace tiny_mesh_viewer::common {

template <typename T>
class WithBind {
 public:
  explicit WithBind(T& t) : t_(t) { this->t_.Bind(); }

  ~WithBind() { this->t_.Unbind(); }

 private:
  T& t_;
};

template <typename T>
class WithUse {
 public:
  explicit WithUse(T& t) : t_(t) { this->t_.Use(); }

  ~WithUse() { this->t_.Unuse(); }

 private:
  T& t_;
};

}  // namespace tiny_mesh_viewer::common

#endif  // TINY_MESH_VIEWER_COMMON_WITH_H_
