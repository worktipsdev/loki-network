cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME worktipsnet)
project(${PROJECT_NAME} C CXX Swift)

get_filename_component(WORKTIPSNET_ROOT .. ABSOLUTE BASE_DIR "${CMAKE_CURRENT_LIST_DIR}")

include("${WORKTIPSNET_ROOT}/cmake/target_link_libraries_system.cmake")
include("${WORKTIPSNET_ROOT}/cmake/add_import_library.cmake")
include("${WORKTIPSNET_ROOT}/cmake/add_log_tag.cmake")
include("${WORKTIPSNET_ROOT}/cmake/libatomic.cmake")

if (STATIC_LINK AND STATIC_LINK_RUNTIME)
  message(FATAL "Cannot set both STATIC_LINK and STATIC_LINK_RUNTIME")
endif()

set(CMAKE_Swift_LANGUAGE_VERSION 5.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${WORKTIPSNET_ROOT}/cmake")

include(FetchContent)
FetchContent_Declare(
    libuv
    GIT_REPOSITORY https://github.com/libuv/libuv.git
    GIT_TAG v1.32.0
)
FetchContent_Populate(libuv)
add_subdirectory(${libuv_SOURCE_DIR} ${libuv_BINARY_DIR})

include("${WORKTIPSNET_ROOT}/cmake/basic_definitions.cmake")
set(LIBUV_IN_SOURCE ON)
set(LIBUV_LIBRARY uv_a)
include("${WORKTIPSNET_ROOT}/cmake/unix.cmake")
unset(LIBTUNTAP_SRC)

find_package(Threads REQUIRED)

set(ABSEIL_DIR "${WORKTIPSNET_ROOT}/vendor/abseil-cpp")

macro(add_worktips_dir name)
    add_subdirectory("${WORKTIPSNET_ROOT}/${name}" "${name}")
endmacro()

include_directories(SYSTEM ${ABSEIL_DIR})
add_worktips_dir(vendor/cxxopts)
add_worktips_dir(vendor/nlohmann)
include_directories(SYSTEM "${WORKTIPSNET_ROOT}/vendor/cxxopts/include")
include_directories("${WORKTIPSNET_ROOT}/include")
include_directories("${libuv_SOURCE_DIR}/include")

add_worktips_dir(vendor/gtest)
add_subdirectory(${ABSEIL_DIR} "vendor/abseil-cpp")

add_worktips_dir(crypto)
add_worktips_dir(llarp)
add_worktips_dir(libabyss)

add_subdirectory(worktipsnet)
