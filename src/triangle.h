//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_TRIANGLE_H
#define CANARYRENDER_TRIANGLE_H
#include "base.h"
#include "m_texture.h"
class Triangle{
public:
    Eigen::Vector4f v[3];
    Eigen::Vector3f colour[3];
    Eigen::Vector3f normal[3];
    Eigen::Vector2f textureUV[3];  // u,v map-axis
    MTexture *texture = nullptr;
    Triangle();
    void boundTexture(MTexture *rhs);
    void setColour(int idx, const Eigen::Vector3f &rhs);
    void setColour(const std::array<Eigen::Vector3f, 3> &rhs);
    void setNormal(int idx, const Eigen::Vector3f &rhs);
    void setNormal(const std::array<Eigen::Vector3f, 3> &rhs);
    void setVertex(int idx, const Eigen::Vector4f &rhs);
    void setVertex(const std::array<Eigen::Vector4f, 3> &rhs);
    void setTextureUV(int idx, const Eigen::Vector3f &rhs);
    void setTextureUV(const std::array<Eigen::Vector3f, 3> &rhs);
};

#endif //CANARYRENDER_TRIANGLE_H
