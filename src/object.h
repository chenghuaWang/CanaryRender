//
// Created by wang on 2022/2/1.
//
#pragma once
#ifndef CANARYRENDER_OBJECT_H
#define CANARYRENDER_OBJECT_H
#include "base.h"
#include "triangle.h"
#include "m_texture.h"
#include "./phaser/cfg_phaser.h"
class Object{
public:
    Object() = delete;
    explicit Object(const CanaryPhaser::objCfgNode &rhs);
    ~Object();
    MTexture *texture = nullptr;
    MTexture *high_map = nullptr;
    std::vector<Triangle*> TriangleList;
};

#endif //CANARYRENDER_OBJECT_H
