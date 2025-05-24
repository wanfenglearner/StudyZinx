
#最小版本要求
cmake_minimum_required(VERSION 3.0)

project(zinxStudy)

#构建Debug环境
set(CMAKE_BUILD_TYPE Debug)

#C++标准
set(CMAKE_CXX_STANDARD 14)

#设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#搜索头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#搜索源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC)

#库目录搜索
link_directories(/usr/lib/)

#可执行文件生成
add_executable(zinx_study ${SRC})

#链接动态库
target_link_libraries(zinx_study zinx pthread)



