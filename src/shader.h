//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_SHADER_H
#define CANARYRENDER_SHADER_H
#include "base.h"
#include "m_texture.h"
/* This shader file for rasterization only.
 * */
class FragmentShaderUnit{
public:
    FragmentShaderUnit() = delete;
    FragmentShaderUnit(Eigen::Vector3f &a, Eigen::Vector3f &b, Eigen::Vector3f &c, Eigen::Vector2f &d, MTexture *mtex):
                        viewPos(a),colour(b),normal(c),textureUV(d), texture(mtex){}
    Eigen::Vector3f viewPos;
    Eigen::Vector3f colour;
    Eigen::Vector3f normal;
    Eigen::Vector2f textureUV;
    MTexture *texture = nullptr;
};

class VertexShaderUnit{
public:
    VertexShaderUnit() = delete;
    explicit VertexShaderUnit(Eigen::Vector3f &rhs):Pos(rhs){}
    Eigen::Vector3f Pos;
};

namespace MShader{

}

#endif //CANARYRENDER_SHADER_H
