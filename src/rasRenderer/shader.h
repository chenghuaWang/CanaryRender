//
// Created by wang on 2022/2/1.
//
#pragma once
#ifndef CANARYRENDER_SHADER_H
#define CANARYRENDER_SHADER_H
#include <utility>

#include "base.h"
#include "material.h"
#include "m_texture.h"
/* This shader file for rasterization only.
 * */
class FragmentShaderUnit{
public:
    FragmentShaderUnit() = delete;
    FragmentShaderUnit(Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector2f d, MTexture *mtex, std::vector<light> _l):
                        CameraPos(std::move(a)), colour(std::move(b)),normal(std::move(c)),textureUV(std::move(d)), texture(mtex), _light(std::move(_l)){}
    Eigen::Vector3f viewPos;
    Eigen::Vector3f colour;
    Eigen::Vector3f normal;
    Eigen::Vector2f textureUV;
    Eigen::Vector3f CameraPos;
    std::vector<light> _light{};
    MTexture *texture = nullptr;
    void setViewPos(const Eigen::Vector3f &rhs);
};

class VertexShaderUnit{
public:
    VertexShaderUnit() = delete;
    explicit VertexShaderUnit(Eigen::Vector3f &rhs):Pos(rhs){}
    Eigen::Vector3f Pos;
};

namespace MShader{
    /* self defined shader should write in here.
     * */
    Eigen::Vector3f PhongFragmentSahder(const FragmentShaderUnit &rhs);
    Eigen::Vector3f TexturePhongFragmentFhader(const FragmentShaderUnit &rhs);
}

#endif //CANARYRENDER_SHADER_H
