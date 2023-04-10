cmake_minimum_required(VERSION 3.26)

file(READ ${CMAKE_SOURCE_DIR}/version.txt PROJECT_VERSION)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)

project(tiny-mesh-viewer VERSION ${PROJECT_VERSION})

set(DATA_DIR ${CMAKE_SOURCE_DIR}/data)
set(DEMO_DIR ${CMAKE_SOURCE_DIR}/demo)
set(DOCUMENTATION_DIR ${CMAKE_SOURCE_DIR}/documentation)
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resource)
set(SCRIPT_DIR ${CMAKE_SOURCE_DIR}/script)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/source)
set(TARGET viewer)

include(cmake/debug.cmake)
include(cmake/filesystem.cmake)
include(cmake/lint.cmake)
include(cmake/pretty.cmake)
include(cmake/sanitizers.cmake)

if(UNIX)
  merge_directories(
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/OpenMesh
    ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/share/openmesh)
endif()

add_subdirectory(${DATA_DIR})
add_subdirectory(${DEMO_DIR})
add_subdirectory(${DOCUMENTATION_DIR})
add_subdirectory(${RESOURCE_DIR})
add_subdirectory(${SOURCE_DIR})
