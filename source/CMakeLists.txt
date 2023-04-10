cmake_minimum_required(VERSION 3.26)

file(GLOB_RECURSE SOURCE_LIST ${SOURCE_DIR}/*.cc)

add_executable(${TARGET} ${SOURCE_LIST})
target_compile_features(${TARGET} PUBLIC cxx_std_17)
# target_compile_features(${TARGET} PUBLIC cxx_std_20)
target_include_directories(${TARGET} PRIVATE ${SOURCE_DIR})
target_link_libraries(${TARGET} PRIVATE resource)

set(FULL_TARGET
    ${TARGET}-${VCPKG_TARGET_TRIPLET}-${CMAKE_BUILD_TYPE}${CMAKE_EXECUTABLE_SUFFIX}
)
string(TOLOWER ${FULL_TARGET} FULL_TARGET)
set(FULL_TARGET ${CMAKE_SOURCE_DIR}/dist/${FULL_TARGET})
add_custom_target(
  ${TARGET}-triplet ALL
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET}> ${FULL_TARGET}
  BYPRODUCTS ${FULL_TARGET}
  VERBATIM)

find_package(Boost REQUIRED)
target_link_libraries(${TARGET} PRIVATE Boost::boost)

# this is heuristically generated, and may not be correct
find_package(cxxopts CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE cxxopts::cxxopts)

find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")
target_include_directories(${TARGET} PRIVATE ${DBG_MACRO_INCLUDE_DIRS})

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE fmt::fmt)

# Or use the header-only version find_package(fmt CONFIG REQUIRED)
# target_link_libraries(${TARGET} PRIVATE fmt::fmt-header-only)

# this is heuristically generated, and may not be correct
find_package(glad CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE glad::glad)

# this is heuristically generated, and may not be correct
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE glfw)

# this is heuristically generated, and may not be correct
find_package(glm CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE glm::glm)

find_package(openmesh REQUIRED)
target_include_directories(${TARGET} PRIVATE ${OPENMESH_INCLUDE_DIRS})
target_link_libraries(${TARGET} PRIVATE ${OPENMESH_LIBRARIES})

# this is heuristically generated, and may not be correct
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE spdlog::spdlog
                                        spdlog::spdlog_header_only)

# this is heuristically generated, and may not be correct
find_package(yaml-cpp CONFIG REQUIRED)
target_link_libraries(${TARGET} PRIVATE yaml-cpp)
