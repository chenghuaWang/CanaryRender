//
// Created by wang on 2022/2/1.
//

#include "rasterization.h"

void rasterizer::setModel(const Eigen::Matrix4f &rhs) { M = rhs;}

void rasterizer::setView(const Eigen::Matrix4f &rhs) { V = rhs;}

void rasterizer::setProjection(const Eigen::Matrix4f &rhs) { P = rhs;}

void rasterizer::addObject(const Object &rhs) { Obj.push_back(rhs);}

rasterizer::rasterizer(int _width, int _height):width(_width), height(_height){
    FragmentBuf.resize(width * height);
    ZBuf.resize(width * height);
    clearBuffer();
}

void rasterizer::clearBuffer() {
    std::fill(FragmentBuf.begin(), FragmentBuf.end(), Eigen::Vector3f({0,0,0}));
    std::fill(ZBuf.begin(), ZBuf.end(), std::numeric_limits<float>::infinity());
}
