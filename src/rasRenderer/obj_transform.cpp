//
// Created by wang on 2022/2/1.
//

#include "obj_transform.h"
Eigen::Matrix4f objtrans::getViewMatrix(Eigen::Vector3f eye_pos){
    Eigen::Matrix4f translate;
    translate << 1,0,0,-eye_pos[0],
            0,1,0,-eye_pos[1],
            0,0,1,-eye_pos[2],
            0,0,0,1;
    return translate;
}

Eigen::Matrix4f objtrans::getYRotationMatrix(float angle){
    Eigen::Matrix4f rotation;
    angle = angle * Canary_PI / 180.f;
    rotation << cosf(angle), 0, sinf(angle), 0,
            0, 1, 0, 0,
            -sinf(angle), 0, cosf(angle), 0,
            0, 0, 0, 1;

    Eigen::Matrix4f scale;
    scale << 2.5, 0, 0, 0,
            0, 2.5, 0, 0,
            0, 0, 2.5, 0,
            0, 0, 0, 1;

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;

    return translate * rotation * scale;
}

Eigen::Matrix4f objtrans::getRotationMatrix(Eigen::Vector3f &n, float angle){
    /* Rodrigues’ Rotation Formula
     * Get view matrix by Rodrigues’ Rotation Formula.
     * */
    float cos_angle = cosf((angle/180.f)*Canary_PI);
    float sin_angle = sinf((angle/180.f)*Canary_PI);
    Eigen::Matrix3f tmp = Eigen::Matrix3f::Zero();
    Eigen::Vector3f normal_axis = n.normalized();
    tmp << 0, -normal_axis.z(), normal_axis.y(),
            normal_axis.z(), 0, -normal_axis.x(),
            -normal_axis.y(), normal_axis.x(), 0;
    tmp = (cos_angle * Eigen::Matrix3f::Identity() + (1-cos_angle) * normal_axis * normal_axis.transpose()) + sin_angle * tmp;
    Eigen::Matrix4f ans_matrix = Eigen::Matrix4f::Zero();
    ans_matrix.block(0, 0, 2, 2) = tmp.block(0,0,2,2);
    return ans_matrix;
}

Eigen::Matrix4f objtrans::getOrthographicMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar){
    /* Orthographic projection. Not use directly.
     * You should give the bounding box based on l,r,t,b,n,f.(calculate from fov, ratio)
     * And Orthographic projection matrix aimed to transfer [l,r]x[b,t]x[f,n]->[-1,1]^3;(In implement, drop Z-axis)
     * */
    float halve = Canary_PI * ((eye_fov/2.0f)/180.0f);
    float t = tanf(halve) * abs(zNear);
    float b = -t;
    float r = aspect_ratio * t;
    float l = -r;
    Eigen::Matrix4f tmp1=Eigen::Matrix4f::Identity(), tmp2=Eigen::Matrix4f::Identity();
    tmp1(0,0) = 2.f/(r-l);
    tmp1(1,1) = 2.f/(t-b);
    tmp1(2,2) = 2.f/(zNear-zFar);
    tmp2(0,3) = -((r+l)/2.f);
    tmp2(1,3) = -((t+b)/2.f);
    tmp2(2,3) = -((zNear+zFar)/2.f);
    return tmp1 * tmp2;
}

Eigen::Matrix4f objtrans::getPerspectiveMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar){
    /* Perspective projection.
     * You should give the bounding box based on l,r,t,b,n,f.(calculate from fov, ratio)
     * Actually, this function will not use objtrans::getOrthographicMatrix to save a little computation.
     * */
    float halve = Canary_PI * ((eye_fov/2.0f)/180.0f);
    float t = -tan(halve) * abs(zNear);
    float b = -t;
    float r = aspect_ratio * t;
    float l = -r;
    Eigen::Matrix4f pers2ort, tmp1=Eigen::Matrix4f::Identity(), tmp2=Eigen::Matrix4f::Identity();
    pers2ort << zNear, 0, 0, 0,
                0, zNear, 0, 0,
                0, 0, zNear+zFar, -zNear*zFar,
                0, 0, 1.f, 0;
    tmp1(0,0) = 2.f/(r-l);
    tmp1(1,1) = 2.f/(t-b);
    tmp1(2,2) = 2.f/(zNear-zFar);
    tmp2(0,3) = -((r+l)/2.f);
    tmp2(1,3) = -((t+b)/2.f);
    tmp2(2,3) = -((zNear+zFar)/2.f);
    return tmp1 * tmp2 * pers2ort;
}

Eigen::Matrix4f objtrans::getViewPortMatrix(int width, int height){
    Eigen::Matrix4f ans;
    ans << float(width)/2.f, 0, 0, float(width)/2.f,
            0, float(height)/2.f, 0, float(height)/2.f,
            0, 0, 1, 0,
            0, 0, 0, 1;
    return ans;
}
