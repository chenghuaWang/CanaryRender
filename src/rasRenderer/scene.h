//
// Created by wang on 2022/2/1.
//
#pragma once
#ifndef CANARYRENDER_SCENE_H
#define CANARYRENDER_SCENE_H
#include "base.h"
#include "../phaser/cfg_phaser.h"
#include "object.h"
#include "material.h"
#include "rasterization.h"
#include "shader.h"
#include "obj_transform.h"
namespace CanaryScene{
    class scene{
    public:
        scene() = delete;
        scene(const std::string &rhs, int _width, int _height, float _fov, float _ratio, float zn, float zf);
        void process(float angle, Eigen::Vector3f &n);
        void process(float angle);
        void addLight(light &rhs);
        void changeCameraPos(Eigen::Vector3f &rhs);
        rasterizer r;
    private:
        float cam_fov, aspect_ratio, zNear, zFar;
        CanaryPhaser::option config;
        Eigen::Vector3f CameraPos = {0,0,10};
    };
}

#endif //CANARYRENDER_SCENE_H
