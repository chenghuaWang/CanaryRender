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
set(PHASER_SRCS ./src/phaser/OBJ_Loader.h src/phaser/OBJ_Loader.cpp
        src/phaser/argument_phaser.cpp src/phaser/argument_phaser.h
        src/phaser/cfg_phaser.cpp src/phaser/cfg_phaser.h)
set(SRCS src/rasRenderer/object.cpp src/rasRenderer/object.h
        src/rasRenderer/material.cpp src/rasRenderer/material.h
        src/rayRenderer/bvh.cpp src/rayRenderer/bvh.h
        src/rayRenderer/sah.cpp src/rayRenderer/sah.h
        src/rasRenderer/triangle.cpp src/rasRenderer/triangle.h
        src/rayRenderer/RayTraceRenderer.cpp src/rayRenderer/RayTraceRenderer.h
        src/rasRenderer/obj_lod.cpp src/rasRenderer/obj_lod.h
        src/rasRenderer/rasterization.cpp src/rasRenderer/rasterization.h
        src/rasRenderer/obj_transform.cpp src/rasRenderer/obj_transform.h
        src/rasRenderer/scene.cpp src/rasRenderer/scene.h
        src/rasRenderer/m_texture.cpp src/rasRenderer/m_texture.h
        src/rayRenderer/base_rt.cpp src/rayRenderer/base_rt.h
        src/rasRenderer/base.h
        src/rasRenderer/ras_anti_aliasing.cpp src/rasRenderer/ras_anti_aliasing.h
        src/rasRenderer/shader.cpp src/rasRenderer/shader.h
        src/rayRenderer/Ray.cpp src/rayRenderer/Ray.h
        src/rayRenderer/object_ray.cpp src/rayRenderer/object_ray.h
        src/rayRenderer/Light.cpp src/rayRenderer/Light.h)

MESSAGE("main file load ${ALL_SRCS}")
MESSAGE("/src/phaser/ file load ${PHASER_SRCS}")
MESSAGE("/src/ file load ${SRCS}")
MESSAGE("All file found.")

add_executable(CanaryRender ${ALL_SRCS} ${PHASER_SRCS} ${SRCS})
target_link_libraries(CanaryRender ${OpenCV_LIBRARIES})
target_link_libraries(CanaryRender Eigen3::Eigen)
