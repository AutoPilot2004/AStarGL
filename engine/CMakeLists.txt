file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_library(engine ${SRC_FILES} "Window/Window.h" "Window/WindowSettings.h"  "Core.h" "Logger/Logger.h" "Logger/Logger.cpp" "Core.cpp" "Management/Events/Dispatcher.h"  "Management/Events/EventManager.cpp" "Management/Events/Input.h" "Management/Events/KeyCodes.h" "Management/Events/Input.cpp" "Graphics/Buffer.h" "Graphics/Buffer.cpp" "Graphics/VertexBuffer.h" "Graphics/VertexBuffer.cpp" "Graphics/ElementBuffer.h" "Graphics/ElementBuffer.cpp" "Graphics/Shader.cpp" "Graphics/Shader.h" "Shapes/Shapes.h" "Math/Transform2D.h" "Math/Transform2D.cpp" "Graphics/ShaderStorageBuffer.h" "Graphics/ShaderStorageBuffer.cpp" "Graphics/VertexArray.h" "Graphics/VertexArray.cpp" "Renderer/Renderer2D.h" "Renderer/Renderer2D.cpp" "Math/Transform.h" "Math/Projection.h" "Math/Projection.cpp" "Scene/Camera2D.h" "Scene/Camera2D.cpp" "Management/Textures/TextureManager.h" "Management/Textures/TextureManager.cpp" "Graphics/Texture.h" "Renderer/RenderCommand.h" "Renderer/RenderCommand.cpp")

target_compile_definitions(engine PRIVATE ENGINE)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Stb_INCLUDE_DIR})
target_link_libraries(engine PUBLIC glfw GLEW::GLEW glm::glm spdlog::spdlog)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET engine PROPERTY CXX_STANDARD 20)
endif()