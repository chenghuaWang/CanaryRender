//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_M_TEXTURE_H
#define CANARYRENDER_M_TEXTURE_H
#include "base.h"
class MTexture{
public:
    MTexture() = delete;
    explicit MTexture(const std::string &rhs){
        std::cout << "info>> get " << rhs << " success." << std::endl;
        MTimage = cv::imread(rhs);
        width = MTimage.cols;
        height = MTimage.rows;
    }
    int Width() const {return width;}
    int Height() const {return height;}
    Eigen::Vector3f colorAt(float u, float v);
private:
    cv::Mat MTimage;
    int width;
    int height;
};

#endif //CANARYRENDER_M_TEXTURE_H
