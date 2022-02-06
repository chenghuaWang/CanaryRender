//
// Created by wang on 2022/2/6.
//
#pragma once
#ifndef CANARYRENDER_RAY_H
#define CANARYRENDER_RAY_H
#include "base_rt.h"
using namespace Eigen;
class Ray{
public:
    Ray(Vector3f _ori, Vector3f _des, float _t):ori(std::move(_ori)),des(std::move(_des)),
    des_inv(1.f/_des.x(),1.f/_des.y(),1.f/_des.z()),_time_(_t){
        t_min = 0.f;
        t_max = std::numeric_limits<float>::max();
    }
    Vector3f ori, des, des_inv;
    float _time_, t_min, t_max;
    Vector3f operator()(float t);
};

#endif //CANARYRENDER_RAY_H
