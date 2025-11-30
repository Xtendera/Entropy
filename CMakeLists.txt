cmake_minimum_required(VERSION 3.16)
project(entropy)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SDLTTF_HARFBUZZ ON CACHE BOOL "Use harfbuzz for text shaping" FORCE)
set(SDLTTF_VENDORED ON CACHE BOOL "Use vendored freetype/harfbuzz" FORCE)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

set(EXE_TYPE "")
if(WIN32)
  set(EXE_TYPE WIN32)
elseif(APPLE)
  set(EXE_TYPE MACOSX_BUNDLE)
elseif(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html" CACHE INTERNAL "")
endif()

add_executable(entropy ${EXE_TYPE})

target_sources(entropy PRIVATE
  src/main.cpp
  src/game.cpp
  src/texture/texture.cpp
  src/texture/sprite_sheet.cpp
  src/texture/texture_manager.cpp
  src/engine/engine.cpp
  src/emitter/emitter.cpp
  src/physics/motion.cpp
  src/time/frame_manager.cpp
  src/time/timer.cpp
  src/scene/scene_manager.cpp
  src/levels/menu.cpp
  src/levels/sandbox.cpp
  src/ui/button.cpp
)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(entropy copy_assets)

# Link to the actual SDL3 library.
target_link_libraries(entropy PRIVATE SDL3_image::SDL3_image SDL3::SDL3 SDL3_ttf::SDL3_ttf)

if(EMSCRIPTEN)
  target_link_options(entropy PRIVATE
    "SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets@/assets"
  )
endif()
