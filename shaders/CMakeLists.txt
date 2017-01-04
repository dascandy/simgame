

function(add_resource_library NAME) 
  set(ALL_SOURCES )
  foreach (RESOURCE ${ARGN})
    set(CPPFILENAME ${PROJECT_BINARY_DIR}/${RESOURCE}.cpp)
    add_custom_command(
            COMMAND to_cpp.sh ${RESOURCE} ${PROJECT_SOURCE_DIR}/${RESOURCE} >${CPPFILENAME}
            DEPENDS ${PROJECT_SOURCE_DIR}/${RESOURCE}
            OUTPUT ${CPPFILENAME}
      )
    LIST(APPEND ALL_SOURCES ${CPPFILENAME})
  endforeach()
  add_library(${NAME}
    ${ALL_SOURCES}
  )
endfunction()

project(shaders)

add_resource_library(${PROJECT_NAME}
  gamescene.frag
  gamescene.vert
)

