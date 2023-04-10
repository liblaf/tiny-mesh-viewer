include_guard()

function(merge_directories FROM TO)
  file(GLOB_RECURSE FILES ${FROM}/*)
  foreach(FILE IN LISTS FILES)
    configure_file(${FILE} ${TO} COPYONLY)
  endforeach()
endfunction()
