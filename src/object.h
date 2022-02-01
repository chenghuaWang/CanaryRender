//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_OBJECT_H
#define CANARYRENDER_OBJECT_H
#include "base.h"
#include "triangle.h"
#include "./phaser/cfg_phaser.h"
#include "./phaser/OBJ_Loader.h"
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
