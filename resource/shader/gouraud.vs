#version 330 core

in vec3 vertex_position; // local space
in vec3 vertex_normal;   // local space

out vec3 vertex_color;

uniform mat4 model_view;    // local space -> world space
uniform mat4 normal_matrix; // local space -> world space
uniform mat4 projection;    // world space -> view space

uniform float ambient_reflection;
uniform float diffuse_reflection;
uniform float specular_reflection;
uniform float shininess;

uniform vec3 camera_position;
uniform vec3 ambient_light_color;
uniform vec3 point_light_position;
uniform vec3 point_light_color;
uniform vec3 object_color;

vec3 ambient() {
  return ambient_reflection * ambient_light_color * object_color;
}

vec3 diffuse(vec3 position, vec3 normal) {
  vec3 light_direction = normalize(point_light_position - position);
  float lambertian = max(dot(normal, light_direction), 0.0);
  return diffuse_reflection * lambertian * point_light_color * object_color;
}

vec3 specular(vec3 position, vec3 normal) {
  vec3 light_direction = normalize(point_light_position - position);
  vec3 view_direction = normalize(camera_position - position);
  vec3 reflection_direction = reflect(-light_direction, normal);
  float specular = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
  return specular_reflection * specular * point_light_color;
}

void main() {
  vec4 vertex_position_4 = model_view * vec4(vertex_position, 1.0);
  vec3 position = vertex_position_4.xyz / vertex_position_4.w;
  gl_Position = projection * vertex_position_4;
  vec3 normal = normalize(vec3(normal_matrix * vec4(vertex_normal, 0.0)));
  vec3 ambient_color = ambient();
  vec3 diffuse_color = diffuse(position, normal);
  vec3 specular_color = specular(position, normal);
  vertex_color = ambient_color + diffuse_color + specular_color;
}
