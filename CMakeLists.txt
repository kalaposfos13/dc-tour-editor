cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME dc-tour-editor)

project(${PROJECT_NAME} LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(externals)


set(HEADERS
    src/fmt/args.h
    src/fmt/base.h
    src/fmt/chrono.h
    src/fmt/color.h
    src/fmt/compile.h
    src/fmt/core.h
    src/fmt/format-inl.h
    src/fmt/format.h
    src/fmt/os.h
    src/fmt/ostream.h
    src/fmt/printf.h
    src/fmt/ranges.h
    src/fmt/std.h
    src/fmt/xchar.h
)

set(HEADERS
    ${FMT_HEEADERS}
    src/common/assert.h
    src/common/logging.h
    src/common/types.h
)

set(SOURCES
    src/main.cpp
    src/common/assert.cpp
    src/fmt/format.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(${PROJECT_NAME} PRIVATE src)