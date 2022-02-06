//
// Created by wang on 2022/2/1.
//
#pragma once
#ifndef CANARYRENDER_RASTERIZATION_H
#define CANARYRENDER_RASTERIZATION_H
#include "base.h"
#include "object.h"
#include "triangle.h"
#include "shader.h"
#include "material.h"
class rasterizer{
public:
    enum RasterizeType{WIRED, SOLID};
    rasterizer() = delete;
    rasterizer(int _width, int _height);
    void setModel(const Eigen::Matrix4f &rhs);
    void setView(const Eigen::Matrix4f &rhs);
    void setProjection(const Eigen::Matrix4f &rhs);
    void setViewPort(const Eigen::Matrix4f &rhs);
    void addObject(const Object &rhs);
    void clearObject();
    void clearBuffer();
    void process();
    void setFragmentShader(std::function<Eigen::Vector3f(FragmentShaderUnit)> _fs);
    std::vector<Eigen::Vector3f>& frame();
    std::vector<Eigen::Vector3f> FragmentBuf;
    std::vector<light> Light{};
    Eigen::Vector3f CameraPos;
private:
    int width, height;
    Eigen::Matrix4f M, V, P, ViewPort;
    std::vector<Object> Obj;
    std::vector<float> ZBuf;
    std::function<Eigen::Vector3f(FragmentShaderUnit)> FragmentShader;
    void RasterizeTriangle(const Triangle &t, const std::array<Eigen::Vector3f, 3>& view_pos, int Option);
    void drawTriangle(const Triangle &rhs, const std::array<Eigen::Vector3f, 3> &ViewPos);
    void drawWireTriangle(const Triangle &rhs);
    void drawLine(const Eigen::Vector3f &a, const Eigen::Vector3f &b, const Eigen::Vector3f &colour);
    void drawLine(int x0, int x1, int y0, int y1, const Eigen::Vector3f &colour);
    void drawObject();
    void setPixel(int x, int y, const Eigen::Vector3f &colour);
    int getIdx(int x , int y) const;
    static Eigen::Vector3f getBarycentric(float a, float b, const Triangle &rhs);
    static Eigen::Vector4f Vec3toVec4(Eigen::Vector3f &rhs, float w = 1.f);
    static bool inTriangle(float a, float b,const Triangle &rhs);
};

#endif //CANARYRENDER_RASTERIZATION_H
