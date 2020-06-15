# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.16)

# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. CUR_ALL_SRCS)
aux_source_directory(./vendor/imgui/ IMGUI_SRCS)
aux_source_directory(./tests/ TEST_SRCS)

# 指定生成目标
add_executable(App.o ${CUR_ALL_SRCS} ${IMGUI_SRCS} ${TEST_SRCS})

# 添加链接库
target_link_libraries(App.o glfw3 GLEW assimp)