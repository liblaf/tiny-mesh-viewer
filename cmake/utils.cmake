include_guard()

function(try_find_program VAR_NAME PROGRAM_NAME)
  find_program(${VAR_NAME} ${PROGRAM_NAME})
  if(NOT ${VAR_NAME})
    unset(${VAR_NAME} CACHE)
    message(WARNING "program not found: ${PROGRAM_NAME}")
  endif()
endfunction()
