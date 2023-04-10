include_guard()

include(${CMAKE_CURRENT_LIST_DIR}/utils.cmake)

option(USE_CLANG_TIDY "" ON)

if(USE_CLANG_TIDY)
  try_find_program(CMAKE_CXX_CLANG_TIDY clang-tidy)
endif()

option(USE_CPPLINT "" ON)

if(USE_CPPLINT)
  try_find_program(CMAKE_CXX_CPPLINT cpplint)
  if(DEFINED CMAKE_CXX_CPPLINT)
    list(APPEND CMAKE_CXX_CPPLINT
         --filter=-build/include_subdir,-legal/copyright)
  endif()
endif()
