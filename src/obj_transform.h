//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_OBJ_TRANSFORM_H
#define CANARYRENDER_OBJ_TRANSFORM_H
#include "base.h"
namespace objtrans{
    Eigen::Matrix4f getViewMatrix(Eigen::Vector3f eye_pos);
    Eigen::Matrix4f getRotationMatrix(Eigen::Vector3f &n, float angle);
    Eigen::Matrix4f getYRotationMatrix(float angle);
    Eigen::Matrix4f getOrthographicMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar);
    Eigen::Matrix4f getPerspectiveMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar);
    Eigen::Matrix4f getViewPortMatrix(int width, int height);
}

#endif //CANARYRENDER_OBJ_TRANSFORM_H
