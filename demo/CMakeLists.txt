cmake_minimum_required(VERSION 3.26)

add_custom_target(
  demo-sphere-phong
  COMMAND $<TARGET_FILE:${TARGET}> --config ${DEMO_DIR}/sphere-phong.yaml
  DEPENDS data
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM
  SOURCES ${DEMO_DIR}/sphere-phong.yaml)

add_custom_target(
  demo-sphere-gouraud
  COMMAND $<TARGET_FILE:${TARGET}> --config ${DEMO_DIR}/sphere-gouraud.yaml
  DEPENDS data
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM
  SOURCES ${DEMO_DIR}/sphere-gouraud.yaml)

add_custom_target(
  demo-sphere
  DEPENDS demo-sphere-phong demo-sphere-gouraud
  VERBATIM)

add_custom_target(
  demo-face
  COMMAND $<TARGET_FILE:${TARGET}> --config ${DEMO_DIR}/face.yaml
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM
  SOURCES ${DEMO_DIR}/face.yaml)

add_custom_target(
  demo-full
  COMMAND $<TARGET_FILE:${TARGET}> --config ${DEMO_DIR}/full.yaml
  DEPENDS data
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM
  SOURCES ${DEMO_DIR}/full.yaml)
