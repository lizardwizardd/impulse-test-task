cmake_minimum_required(VERSION 3.10)
project(Computer-Club)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        f8d7d77 
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(class_computerclub STATIC
    src/computerclub.cpp
    src/filebuffer.cpp
    src/mytime.cpp
    src/eventin.cpp
    src/eventout.cpp
)
target_include_directories(class_computerclub PUBLIC include)

add_executable(ComputerClub main.cpp)
target_link_libraries(ComputerClub class_computerclub)


# add_executable(tests 
# )

# target_link_libraries(tests 
#     class_computerclub
#     gtest_main
#     gmock_main
# )