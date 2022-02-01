//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_RASTERIZATION_H
#define CANARYRENDER_RASTERIZATION_H
#include "base.h"
#include "object.h"
#include "triangle.h"
class rasterizer{
public:
    rasterizer() = delete;
    rasterizer(int _width, int _height);
    void setModel(const Eigen::Matrix4f &rhs);
    void setView(const Eigen::Matrix4f &rhs);
    void setProjection(const Eigen::Matrix4f &rhs);
    void addObject(const Object &rhs);
    void clearBuffer();
    void run();
private:
    int width, height;
    Eigen::Matrix4f M, V, P;
    std::vector<Object> Obj;
    std::vector<Eigen::Vector3f> FragmentBuf;
    std::vector<float> ZBuf;
    void RasterizeTriangle(const Triangle &t, const std::array<Eigen::Vector3f, 3>& view_pos);
    void drawTriangle(const Triangle &rhs);
    void drawObject(const Object &rhs);
};

#endif //CANARYRENDER_RASTERIZATION_H
