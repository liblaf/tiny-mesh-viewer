include_guard()

include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

add_custom_target(pretty)

try_find_program(CLANG_FORMAT clang-format)
if(DEFINED CLANG_FORMAT)
  file(GLOB_RECURSE SRC_LIST ${SOURCE_DIR}/*.cpp ${SOURCE_DIR}/*.h)
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT} -i ${SRC_LIST}
    VERBATIM)
  add_dependencies(pretty clang-format)
endif()

try_find_program(CMAKE_FORMAT cmake-format)
if(DEFINED CMAKE_FORMAT)
  file(GLOB_RECURSE CMAKE_LIST ${CMAKE_SOURCE_DIR}/CMakeLists.txt
       ${CMAKE_SOURCE_DIR}/cmake/*.cmake)
  add_custom_target(
    cmake-format
    COMMAND ${CMAKE_FORMAT} --in-place ${CMAKE_LIST}
    VERBATIM)
  add_dependencies(pretty cmake-format)
endif()

try_find_program(ISORT isort)
if(DEFINED ISORT)
  file(GLOB_RECURSE PYTHON_LIST ${SCRIPT_DIR}/*.py)
  add_custom_target(
    isort
    COMMAND ${ISORT} --profile black ${PYTHON_LIST}
    VERBATIM)
  add_dependencies(pretty isort)
endif()

try_find_program(BLACK black)
if(DEFINED BLACK)
  file(GLOB_RECURSE PYTHON_LIST ${SCRIPT_DIR}/*.py)
  add_custom_target(
    black
    COMMAND ${BLACK} ${PYTHON_LIST}
    VERBATIM)
  add_dependencies(pretty black)
endif()
