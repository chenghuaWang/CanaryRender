cmake_minimum_required(VERSION 3.20)
project(CanaryRender)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(/openmp)

set(DEigen3_DIR D:/commonlib/eigen-3.4.0/cmake/)
FIND_PACKAGE (Eigen3 3.3 NO_MODULE)
INCLUDE_DIRECTORIES (${EIGEN3_INCLUDE_DIRS})

set(OpenCV_DIR D:/commonlib/OPENCV/opencv/build/x64/vc15/lib/)
find_package(OpenCV 4.5 REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

aux_source_directory(. ALL_SRCS)
set(PHASER_SRCS ./src/phaser/OBJ_Loader.h
        src/phaser/argument_phaser.cpp src/phaser/argument_phaser.h
        src/phaser/cfg_phaser.cpp src/phaser/cfg_phaser.h)
set(SRCS ./src/object.cpp ./src/object.h
        src/material.cpp src/material.h
        src/bvh.cpp src/bvh.h
        src/sah.cpp src/sah.h
        src/triangle.cpp src/triangle.h
        src/ray_trace.cpp src/ray_trace.h
        src/obj_lod.cpp src/obj_lod.h
        src/rasterization.cpp src/rasterization.h
        src/obj_transform.cpp src/obj_transform.h
        src/scene.cpp src/scene.h
        src/m_texture.cpp src/m_texture.h
        src/base_global.cpp src/base_global.h
        src/base.h
        src/ras_anti_aliasing.cpp src/ras_anti_aliasing.h
        src/shader.cpp src/shader.h)

MESSAGE("main file load ${ALL_SRCS}")
MESSAGE("/src/phaser/ file load ${PHASER_SRCS}")
MESSAGE("/src/ file load ${SRCS}")
MESSAGE("All file found.")

add_executable(CanaryRender ${ALL_SRCS} ${PHASER_SRCS} ${SRCS})
target_link_libraries(CanaryRender ${OpenCV_LIBRARIES})
target_link_libraries(CanaryRender Eigen3::Eigen)
