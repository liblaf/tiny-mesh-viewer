include_guard()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  option(DEBUG_UNIFORM "GLSL Uniform Variables" ON)
  option(DEBUG_CAMERA "" ON)
  option(DEBUG_AMBIENT_LIGHT "" ON)
  option(DEBUG_POINT_LIGHT "" ON)
  option(DEBUG_WINDOW "" ON)
else()
  option(DEBUG_UNIFORM "GLSL Uniform Variables" OFF)
  option(DEBUG_CAMERA "" OFF)
  option(DEBUG_AMBIENT_LIGHT "" OFF)
  option(DEBUG_POINT_LIGHT "" OFF)
  option(DEBUG_WINDOW "" OFF)
endif()

if(DEBUG_UNIFORM)
  add_compile_definitions("DEBUG_UNIFORM")
endif()

if(DEBUG_CAMERA)
  add_compile_definitions("DEBUG_CAMERA")
endif()

if(DEBUG_AMBIENT_LIGHT)
  add_compile_definitions("DEBUG_AMBIENT_LIGHT")
endif()

if(DEBUG_POINT_LIGHT)
  add_compile_definitions("DEBUG_POINT_LIGHT")
endif()

if(DEBUG_WINDOW)
  add_compile_definitions("DEBUG_WINDOW")
endif()
