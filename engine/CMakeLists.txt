cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SRC_FILES ./*.cpp)

set(ENGINE_NAME engine)

add_library(${ENGINE_NAME} ${SRC_FILES} "Window/Window.h" "Window/WindowSettings.h"  "Core.h" "Logger/Logger.h" "Logger/Logger.cpp" "Core.cpp" "Management/Events/Dispatcher.h"  "Management/Events/EventManager.cpp" "Management/Events/Input.h" "Management/Events/KeyCodes.h" "Management/Events/Input.cpp" "Graphics/Buffer.h" "Graphics/Buffer.cpp" "Graphics/VertexBuffer.h" "Graphics/VertexBuffer.cpp" "Graphics/ElementBuffer.h" "Graphics/ElementBuffer.cpp" "Graphics/Shader.cpp" "Graphics/Shader.h" "Shapes/Shapes.h" "Math/Transform2D.h" "Math/Transform2D.cpp" "Graphics/ShaderStorageBuffer.h" "Graphics/ShaderStorageBuffer.cpp" "Graphics/VertexArray.h" "Graphics/VertexArray.cpp" "Renderer/Renderer2D.h" "Renderer/Renderer2D.cpp" "Math/Transform.h" "Math/Projection.h" "Math/Projection.cpp" "Scene/Camera2D.h" "Scene/Camera2D.cpp" "Management/Textures/TextureManager.h" "Management/Textures/TextureManager.cpp" "Graphics/Texture.h" "Renderer/RenderCommand.h" "Renderer/RenderCommand.cpp" "Contexts/Contexts.h" "Scene/Scene.h" "Scene/Scene.cpp" "Management/Cameras/CameraManager.h" "Management/Cameras/CameraManager.cpp" "Application.h" "Application.cpp" "Defaults.cpp" "Defaults.h" "HF.h" "HF.cpp")

target_compile_definitions(${ENGINE_NAME} PRIVATE ENGINE)
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Stb_INCLUDE_DIR})
target_link_libraries(${ENGINE_NAME} PUBLIC glfw GLEW::GLEW glm::glm spdlog::spdlog)

function(copy_assets target_name)
add_custom_command(TARGET ${target_name} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/engine/Assets" $<TARGET_FILE_DIR:${target_name}>/Assets
  COMMAND_EXPAND_LISTS
  )
endfunction()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${ENGINE_NAME} PROPERTY CXX_STANDARD 23)
endif()