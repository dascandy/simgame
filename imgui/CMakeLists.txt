#
# Copyright (c) YourCompany. All rights reserved.
#

# GENERATED BY CPP-DEPENDENCIES - do not edit, your changes will be lost
# If you must edit, remove these two lines to avoid regeneration

project(imgui)


add_library(${PROJECT_NAME} STATIC
  imconfig.h
  imgui.cpp
  imgui.h
  imgui_draw.cpp
  imgui_impl_glfw_gl3.cpp
  imgui_impl_glfw_gl3.h
  imgui_internal.h
  stb_rect_pack.h
  stb_textedit.h
  stb_truetype.h
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    .
)

include(CMakeAddon.txt)
