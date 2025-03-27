cmake_minimum_required(VERSION 3.14)
include(FetchContent)
include(CMakePrintHelpers)

set(PROJ RAY)
set(LIB raylib)

project (${PROJ} VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set(BUILD_SHARED_LIBS ON)

list(APPEND SOURCE_DIRS  ${PROJECT_SOURCE_DIR}/src)
list(APPEND INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
file(GLOB source_files "${SOURCE_DIRS}/*.cpp")

# add_library(${LIB} ${source_files})
add_library(${LIB} ${PROJECT_SOURCE_DIR}/src/tuples.cpp ${PROJECT_SOURCE_DIR}/src/utils.cpp)
add_executable(canvas_test ${PROJECT_SOURCE_DIR}/tests/canvas.cpp)
add_executable(colors_test ${PROJECT_SOURCE_DIR}/tests/colors.cpp)
add_executable(matrix_test ${PROJECT_SOURCE_DIR}/tests/matrix.cpp)
add_executable(ray_test    ${PROJECT_SOURCE_DIR}/tests/ray.cpp)
add_executable(sphere_test ${PROJECT_SOURCE_DIR}/tests/sphere.cpp)
add_executable(tuple_test  ${PROJECT_SOURCE_DIR}/tests/tuples.cpp)
add_executable(utils_test  ${PROJECT_SOURCE_DIR}/tests/utils.cpp)

# Custom boost dir
# set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/libs/boost")
# set(Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )

# set(Boost_NO_BOOST_CMAKE         ON)
# set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
# set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
# set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME    OFF)
# find_package(Boost 1.75.0 REQUIRED COMPONENTS date_time regex system thread)
# list(APPEND INCLUDE_DIRS ${Boost_INCLUDE_DIRS})

# FetchContent_Declare(fmt
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG 10.2.1
# )
# FetchContent_MakeAvailable(fmt)
# 
# FetchContent_Declare(spdlog
#   GIT_REPOSITORY https://github.com/gabime/spdlog.git
#   GIT_TAG v1.14.1
# )
# FetchContent_MakeAvailable(spdlog)
# 
# FetchContent_Declare(mega
#   GIT_REPOSITORY git@github.com:yetibob/mega-cpp.git
#   GIT_TAG main
# )
# FetchContent_MakeAvailable(mega)

# list(APPEND EXTRA_LIBS spdlog fmt::fmt mega ${Boost_LIBRARIES})

include_directories(${LIB} PUBLIC
    ${INCLUDE_DIRS}
)

target_link_libraries(canvas_test PRIVATE
    ${LIB}
)
target_link_libraries(colors_test PRIVATE
    ${LIB}
)
target_link_libraries(matrix_test PRIVATE
    ${LIB}
)
target_link_libraries(sphere_test PRIVATE
    ${LIB}
)
target_link_libraries(ray_test PRIVATE
    ${LIB}
)
target_link_libraries(tuple_test PRIVATE
    ${LIB}
)
target_link_libraries(utils_test PRIVATE
    ${LIB}
)

option(${PROJ}_TEST "Set whether to run TESTS or not" OFF)
if (${PROJ}_TEST)
    set(test_dir  ${CMAKE_CURRENT_SOURCE_DIR}/tests)
    file(GLOB test_files "${test_dir}/*.cpp")

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
        # GIT_TAG v1.13.0
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_executable(
        ${EXE}_test
        ${test_files}
    )
    target_include_directories(${EXE}_test PRIVATE
        ${INCLUDE_DIRS}
    )

    target_link_libraries(${EXE}_test PRIVATE
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(${EXE}_test)
endif()

find_package(Doxygen)
if (${DOXYGEN_FOUND})
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/docs/doxygen)
    set(DOXYGEN_EXCLUDE_PATTERNS ${CMAKE_CURRENT_BINARY_DIR})
    doxygen_add_docs(doxygen)
endif()
