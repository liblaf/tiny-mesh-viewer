cmake_minimum_required(VERSION 3.26)

file(GLOB_RECURSE RESOURCE_LIST ${RESOURCE_DIR}/*)
list(REMOVE_ITEM RESOURCE_LIST ${RESOURCE_DIR}/CMakeLists.txt)

find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(resource NAMESPACE resource)
cmrc_add_resources(resource WHENCE ${RESOURCE_DIR} ${RESOURCE_LIST})
