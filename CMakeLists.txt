# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.0)

# 项目信息
PROJECT (myOpenGL)

# 设置构建类型，及相应的编译选项
message(STATUS, "ENV{CXXFLAGS}, $ENV{CXXFLAGS}")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -std=c++17 -framework Cocoa -framework OpenGL -framework IOKit")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -O0 -g -ggdb ")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# add_definitions("-DGLFW_INCLUDE_GLCOREARB")
add_definitions("-DGLEW_STATIC")

# 设置执行文件输出目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Debug/bin)
# 设置库输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Debug/lib)

# 头文件搜索目录
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/Dependencies/glfw/3.3.2/include
    ${PROJECT_SOURCE_DIR}/Dependencies/glew/2.1.0_1/include
    ${PROJECT_SOURCE_DIR}/OpenGL/src
    )
# 链接库搜索路径
LINK_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/Dependencies/glfw/3.3.2/lib-macos
    ${PROJECT_SOURCE_DIR}/Dependencies/glew/2.1.0_1/lib
    )

# 添加子目录
ADD_SUBDIRECTORY(OpenGL)