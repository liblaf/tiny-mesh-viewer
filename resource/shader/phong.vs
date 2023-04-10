#version 330 core

layout (location = 0) in vec3 vertex_position; // local space
layout (location = 1) in vec3 vertex_normal;   // local space

out vec3 fragment_position; // world space
out vec3 fragment_normal;   // world space

uniform mat4 model_view;    // local space -> world space
uniform mat4 normal_matrix; // local space -> world space
uniform mat4 projection;    // world space -> view space

void main() {
  vec4 vertex_position_4 = model_view * vec4(vertex_position, 1.0);
  fragment_position = vertex_position_4.xyz / vertex_position_4.w;
  fragment_normal = vec3(normal_matrix * vec4(vertex_normal, 0.0));

  gl_Position = projection * vertex_position_4;
}
