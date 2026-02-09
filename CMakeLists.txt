cmake_minimum_required(VERSION 3.14)
project(RhythmGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_image
FetchContent_Declare(
  SDL3_image
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_image)

# Fetch SDL3_ttf
FetchContent_Declare(
  SDL3_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG main
)
FetchContent_MakeAvailable(SDL3_ttf)

# Fetch nlohmann/json
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(json)

add_executable(RhythmGame
    src/main.cpp
    src/core/App.cpp
    src/core/App.h
    src/core/Context.h
    src/core/Config.h
    src/assets/FontManager.cpp
    src/assets/FontManager.h
    src/utils/StateMachine.cpp
    src/utils/StateMachine.h
    src/utils/IState.h
    src/states/TitleState.cpp
    src/states/TitleState.h
    src/states/MenuState.cpp
    src/states/MenuState.h
)

target_include_directories(RhythmGame PUBLIC
    src
    src/core
    src/utils
    src/game
    src/states
)

target_link_libraries(RhythmGame PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf nlohmann_json::nlohmann_json)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/assets)
