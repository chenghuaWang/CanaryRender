//
// Created by wang on 2022/2/1.
//

#include "rasterization.h"

#include <utility>

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
    std::fill(FragmentBuf.begin(), FragmentBuf.end(), Eigen::Vector3f({255,255,255}));
    std::fill(ZBuf.begin(), ZBuf.end(), std::numeric_limits<float>::infinity());
}

void rasterizer::RasterizeTriangle(const Triangle &t, const std::array<Eigen::Vector3f, 3> &view_pos, int Option) {
    switch (Option) {
        case RasterizeType::WIRED:
            /* In this section Z-buffer is not need.
             * Just use wired triangle to debug if lod worked well.
             * And in this section, shader is not work.
             * I set colour to {0, 0, 0}, while background is {255, 255, 255}
             * */
            drawWireTriangle(t);
        case RasterizeType::SOLID: {
            /* shade fragment.
             * 1. get the bounding box.
             * 2. Calculate interpolate.
             * 3. Go through each pixel. Use modified shader to get its color or texture.
             * 4. Set color and zBuffer.
             * */
            int top = std::ceil(fmax(t.v[0].y(), fmax(t.v[1].y(), t.v[2].y())));
            int bot = std::floor(fmin(t.v[0].y(), fmin(t.v[1].y(), t.v[2].y())));
            int lef = std::floor(fmin(t.v[0].x(), fmin(t.v[1].x(), t.v[2].x())));
            int rig = std::ceil(fmax(t.v[0].x(), fmax(t.v[1].x(), t.v[2].x())));
            for (int x = lef; x <= rig; ++x){
                for (int y = bot; y <= top; ++y){
                    float _px = (float)x + 0.5f, _py = (float)y + 0.5f;
                    float alpha(0.f), beta(0.f), gamma(0.f);
                    if (inTriangle(_px, _py, t)){
                        auto BarycentricCo = getBarycentric(_px, _py, t);
                        alpha = BarycentricCo.x(), beta = BarycentricCo.y(), gamma = BarycentricCo.z();
                        /* Interpolate z, w and normal.
                         * */
                        float w_reciprocal = 1.f / (alpha / t.v[0].w() + beta / t.v[1].w() + gamma / t.v[2].w());
                        float z_interpolated = alpha * t.v[0].z() / t.v[0].w() + beta * t.v[1].z() / t.v[1].w() + gamma * t.v[2].z() / t.v[2].w();
                        z_interpolated *= w_reciprocal;
                        int zbuf_idx = getIdx(x, y);
                        if (z_interpolated < ZBuf[zbuf_idx]){
                            ZBuf[zbuf_idx] = z_interpolated;
                            auto interpolated_color = alpha * t.colour[0] + beta * t.colour[1] + gamma * t.colour[2];
                            auto interpolated_normal = alpha * t.normal[0] + beta * t.normal[1] + gamma * t.normal[2];
                            auto interpolated_texcoords = alpha * t.textureUV[0] + beta * t.textureUV[1] + gamma * t.textureUV[2];
                            auto interpolated_shader = alpha * view_pos[0] + beta * view_pos[1] + gamma * view_pos[2];
                            FragmentShaderUnit FragBlock(CameraPos, interpolated_color, interpolated_normal.normalized(),
                                                         interpolated_texcoords, t.texture, Light);
                            FragBlock.setViewPos(interpolated_shader);
                            auto _colour = FragmentShader(FragBlock);
                            setPixel(x, y, _colour);
                        }
                    }
                }
            }
        }
        break;
        default:
            exit(1);
    }
}

void rasterizer::drawTriangle(const Triangle &rhs, const std::array<Eigen::Vector3f, 3> &ViewPos) {

}

void rasterizer::drawObject() {
    /* draw each triangle in Object Triangle list.
     * 1. Get MVP transform matrix
     * 2. Use M Matrix modify all triangle's position. Then, use V matrix to move Obj to default position.
     * 3. Get view space of each object. Why need view space?
     *      The MVP transformation matrix contains 3 matrix, modify object to position you want, using view
     *      transformation to get right camera place, using projection(perspective by default) to get 2D
     *      position in our screen. While, in 3D rasterization, the projection matrix changed x,y-axis, which
     *      made interpolate hard to process. We need original position(View * Modify * Vertex) to get info
     *      of transformed vertex position.
     * 4. Get MVP transformed position.
     * 5. Use Fragment shader to get correct colour of each pixel.
     * --
     * 6. Get new Normal vector use inv_transformation matrix.
     *      Use (M^{-1})^{T}*normal
     * */
    Eigen::Matrix4f mvp = P * V * M;
    Eigen::Matrix4f view_pos_trans = V * M;
    Eigen::Matrix4f normal_trans = (V*M).inverse().transpose();
    int objLen = Obj.size();
#pragma omp parallel for collapse(2)
    for (int i=0; i<objLen; ++i){ // const auto &obj:Obj
        Object obj = Obj[i];
        int TriangleLen = obj.TriangleList.size();
        for (int j = 0; j<TriangleLen; ++j){ // const auto &tmpTri:obj.TriangleList
            Triangle *tmpTri = obj.TriangleList[j];
            Triangle ShadeTri = *tmpTri;
            std::array<Eigen::Vector3f, 3> ViewPos{
                    (view_pos_trans * tmpTri->v[0]).head<3>(),
                    (view_pos_trans * tmpTri->v[1]).head<3>(),
                    (view_pos_trans * tmpTri->v[2]).head<3>(),
            };
            Eigen::Vector3f newNormal[] = {
                    (normal_trans * Vec3toVec4(tmpTri->normal[0], 0.f)).head<3>(),
                    (normal_trans * Vec3toVec4(tmpTri->normal[1], 0.f)).head<3>(),
                    (normal_trans * Vec3toVec4(tmpTri->normal[2], 0.f)).head<3>(),
            };
            Eigen::Vector4f newV[] = {
                    (mvp * tmpTri->v[0]),
                    (mvp * tmpTri->v[1]),
                    (mvp * tmpTri->v[2])
            };
            for (auto &item:newV){
                item.x() /= item.w();
                item.y() /= item.w();
                item.z() /= item.w();
                item.w() = 1.f;
                item = ViewPort * item;
            }
            for (int k=0;k < 3; ++k){
                ShadeTri.setVertex(k, newV[k]);
                ShadeTri.setNormal(k, newNormal[k]);
            }
            RasterizeTriangle(ShadeTri, ViewPos, RasterizeType::SOLID);
        }
    }
}

void rasterizer::drawLine(const Eigen::Vector3f &a, const Eigen::Vector3f &b, const Eigen::Vector3f &colour) {
    /* Use Bresenham algorithm to draw line defined by 2 points a and b. Z-axis will be dropped.
     * For anti-aliasing, SFD-AABB methods could be used.
     * */
    int x0 = (int)a.x(), x1 = (int)b.x();
    int y0 = (int)a.y(), y1 = (int)b.y();
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (setPixel(x0, y0, colour), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}

void rasterizer::drawLine(int x0, int x1, int y0, int y1, const Eigen::Vector3f &colour) {
    /* Use Bresenham algorithm to draw line defined by 2 points a and b. Z-axis will be dropped.
     * For anti-aliasing, SFD-AABB methods could be used.
     * */
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (setPixel(x0, y0, colour), x0 != x1 || y0 != y1) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 <  dy) { err += dx; y0 += sy; }
    }
}

void rasterizer::setPixel(int x, int y, const Eigen::Vector3f &colour) {
    FragmentBuf[getIdx(x, y)] = colour;
}

int rasterizer::getIdx(int x, int y) const {
    // TODO this method is time consuming, due to cache load law.
    // return x * width + y;
    return (height - y) * width + x;
}

void rasterizer::drawWireTriangle(const Triangle &rhs) {
    drawLine((int)rhs.v[0].x(), (int)rhs.v[1].x(), (int)rhs.v[0].y(), (int)rhs.v[1].y(), {0,0,0});
    drawLine((int)rhs.v[1].x(), (int)rhs.v[2].x(), (int)rhs.v[1].y(), (int)rhs.v[2].y(), {0,0,0});
    drawLine((int)rhs.v[2].x(), (int)rhs.v[0].x(), (int)rhs.v[2].y(), (int)rhs.v[0].y(), {0,0,0});
}

void rasterizer::process() {
    drawObject();
}

void rasterizer::setViewPort(const Eigen::Matrix4f &rhs) {
    ViewPort = rhs;
}

Eigen::Vector4f rasterizer::Vec3toVec4(Eigen::Vector3f &rhs, float w) {
    return Eigen::Vector4f({rhs.x(), rhs.y(), rhs.z(), w});
}

void rasterizer::clearObject() {
    Obj.clear();
}

std::vector<Eigen::Vector3f>& rasterizer::frame() {
    return FragmentBuf;
}

bool rasterizer::inTriangle(float a, float b, const Triangle &rhs) {
    float dx0 = a - rhs.v[0].x(), dy0 = b - rhs.v[0].y();
    float dx1 = a - rhs.v[1].x(), dy1 = b - rhs.v[1].y();
    float dx2 = a - rhs.v[2].x(), dy2 = b - rhs.v[2].y();
    bool j0 = (dx0 * dy1 - dy0 * dx1) > 0;
    bool j1 = (dx1 * dy2 - dy1 * dx2) > 0;
    bool j2 = (dx2 * dy0 - dy2 * dx0) > 0;
    return (j0==j1 && j1 == j2 && j2 == j0);
}

Eigen::Vector3f rasterizer::getBarycentric(float x, float y, const Triangle &rhs) {
    float c1 = (x*(rhs.v[1].y() - rhs.v[2].y()) + (rhs.v[2].x() - rhs.v[1].x())*y + rhs.v[1].x()*rhs.v[2].y()-
            rhs.v[2].x()*rhs.v[1].y()) / (rhs.v[0].x()*(rhs.v[1].y() - rhs.v[2].y())+
                    (rhs.v[2].x() - rhs.v[1].x())*rhs.v[0].y() + rhs.v[1].x()*rhs.v[2].y()-
                    rhs.v[2].x()*rhs.v[1].y());
    float c2 = (x*(rhs.v[2].y() - rhs.v[0].y()) + (rhs.v[0].x() - rhs.v[2].x())*y + rhs.v[2].x()*rhs.v[0].y()-
            rhs.v[0].x()*rhs.v[2].y()) / (rhs.v[1].x()*(rhs.v[2].y() - rhs.v[0].y())+
                    (rhs.v[0].x() - rhs.v[2].x())*rhs.v[1].y() + rhs.v[2].x()*rhs.v[0].y()-
                    rhs.v[0].x()*rhs.v[2].y());
    float c3 = (x*(rhs.v[0].y() - rhs.v[1].y()) + (rhs.v[1].x() - rhs.v[0].x())*y + rhs.v[0].x()*rhs.v[1].y()-
            rhs.v[1].x()*rhs.v[0].y()) / (rhs.v[2].x()*(rhs.v[0].y() - rhs.v[1].y())+
                    (rhs.v[1].x() - rhs.v[0].x())*rhs.v[2].y() + rhs.v[0].x()*rhs.v[1].y()-
                    rhs.v[1].x()*rhs.v[0].y());
    return Eigen::Vector3f ({c1,c2,c3});
}

void rasterizer::setFragmentShader(std::function<Eigen::Vector3f(FragmentShaderUnit)> _fs) {
    FragmentShader = std::move(_fs);
}
