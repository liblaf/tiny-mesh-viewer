include_guard()

set(SANITIZERS
    "address" "undefined"
    CACHE STRING "")

if("address" IN_LIST SANITIZERS)
  add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address)
endif()

if("thread" IN_LIST SANITIZERS)
  add_compile_options(-fsanitize=thread -fno-omit-frame-pointer)
  add_link_options(-fsanitize=thread)
endif()

if("memory" IN_LIST SANITIZERS)
  add_compile_options(-fsanitize=memory -fno-omit-frame-pointer
                      -fsanitize-memory-track-origins)
  add_link_options(-fsanitize=memory)
endif()

if("hwaddress" IN_LIST SANITIZERS)
  add_compile_options(-fsanitize=hwaddress -fno-omit-frame-pointer)
  add_link_options(-fsanitize=hwaddress)
endif()

if("undefined" IN_LIST SANITIZERS)
  add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=undefined)
endif()
