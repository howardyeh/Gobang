# set project's name
PROJECT( Gobang )


# CMake settings
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)
add_definitions(-std=c++11)


FILE(GLOB_RECURSE HDRS_FILES "src/*.h" "src/*.hpp")
FILE(GLOB_RECURSE SRCS_FILES "src/*.c" "src/*.cpp")

ADD_EXECUTABLE(${PROJECT_NAME} ${SRCS_FILES} ${HDRS_FILES})
