#version 330 core

in vec3 fragment_position; // world space
in vec3 fragment_normal;   // world space

out vec4 fragment_color;

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
  float reflection = max(dot(normal, light_direction), 0.0);
  return diffuse_reflection * reflection * point_light_color * object_color;
}

vec3 specular(vec3 position, vec3 normal) {
  vec3 light_direction = normalize(point_light_position - position);
  vec3 view_direction = normalize(camera_position - position);
  vec3 reflection_direction = reflect(-light_direction, normal);
  float reflection = pow(max(dot(view_direction, reflection_direction), 0.0), shininess);
  return specular_reflection * reflection * point_light_color;
}

void main() {
  vec3 position = fragment_position;
  vec3 normal = normalize(fragment_normal);
  vec3 ambient_color = ambient();
  vec3 diffuse_color = diffuse(position, normal);
  vec3 specular_color = specular(position, normal);
  fragment_color = vec4(ambient_color + diffuse_color + specular_color, 1.0);
}
