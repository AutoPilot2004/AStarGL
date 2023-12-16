cmake_minimum_required (VERSION 3.27.0)

file(GLOB_RECURSE SRC_FILES ./*.cpp)
set(app_name astar)

add_executable(${app_name} ${SRC_FILES} "Application.h" "Application.cpp" "Board.h" "Board.cpp" "GameScene.h" "GameScene.cpp" "AStarAlgo.h" "AStarAlgo.cpp" "FadeScene.h" "FadeScene.cpp" "MenuScene.h" "MenuScene.cpp" "SceneID.h")

target_include_directories(${app_name} PRIVATE ../)
target_link_libraries(${app_name} PRIVATE engine)

copy_assets(${app_name})

add_custom_command(TARGET ${app_name} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/AStar/Assets" $<TARGET_FILE_DIR:${app_name}>/Assets
  COMMAND_EXPAND_LISTS
  )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${app_name} PROPERTY CXX_STANDARD 23)
endif()