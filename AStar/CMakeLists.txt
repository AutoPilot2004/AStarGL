cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE SRC_FILES ./*.cpp)

add_executable(astar ${SRC_FILES} "Application.h" "Application.cpp" "Board.h" "Board.cpp" "GameScene.h" "GameScene.cpp" "AStarAlgo.h" "AStarAlgo.cpp" "FadeScene.h" "FadeScene.cpp" "MenuScene.h" "MenuScene.cpp" "SceneID.h")

target_include_directories(astar PRIVATE ../)
target_link_libraries(astar PRIVATE engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET astar PROPERTY CXX_STANDARD 23)
endif()