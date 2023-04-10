cmake_minimum_required(VERSION 3.26)

add_custom_target(
  data
  COMMAND python ${SCRIPT_DIR}/sphere.py --output ${DATA_DIR}/sphere.obj
  # BYPRODUCTS ${DATA_DIR}/sphere.obj ${DATA_DIR}/sphere.mtl
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  VERBATIM
  SOURCES ${SCRIPT_DIR}/sphere.py)
