//
// Created by wang on 2022/2/1.
//

#include "triangle.h"

Triangle::Triangle() {
    for (int i = 0; i < 3; ++i) {
        v[i] << 0, 0, 0, 1;
        colour[i] = Eigen::Vector3f::Zero();
        textureUV[i] = Eigen::Vector2f::Zero();
        normal[i] = Eigen::Vector3f::Zero();
    }
}

void Triangle::setColour(int idx, const Eigen::Vector3f &rhs) {
    /* input should between [0, 255], and this function will normalize it to [0, 1]
     */
    colour[idx] = rhs / 255.f;
}

void Triangle::setColour(const std::array<Eigen::Vector3f, 3> &rhs) {
    /* input should between [0, 255], and this function will normalize it to [0, 1]
     */
    colour[0] = rhs[0] / 255.f;
    colour[1] = rhs[1] / 255.f;
    colour[2] = rhs[2] / 255.f;
}

void Triangle::setNormal(int idx, const Eigen::Vector3f &rhs) {
    normal[idx] = rhs;
}

void Triangle::setNormal(const std::array<Eigen::Vector3f, 3> &rhs) {
    normal[0] = rhs[0];
    normal[1] = rhs[1];
    normal[2] = rhs[2];
}

void Triangle::setVertex(int idx, const Eigen::Vector4f &rhs) {
    v[idx] = rhs;
}

void Triangle::setVertex(const std::array<Eigen::Vector4f, 3> &rhs) {
    v[0] = rhs[0];
    v[1] = rhs[1];
    v[2] = rhs[2];
}

void Triangle::setTextureUV(int idx, const Eigen::Vector3f &rhs) {
    textureUV[idx] = rhs;
}

void Triangle::setTextureUV(const std::array<Eigen::Vector3f, 3> &rhs) {
    textureUV[0] = rhs[0];
    textureUV[1] = rhs[1];
    textureUV[2] = rhs[2];
}

void Triangle::boundTexture(MTexture *rhs) {
    texture = rhs;
}
