//
// Created by wang on 2022/2/1.
//

#include "m_texture.h"

Eigen::Vector3d MTexture::colorAt(float u, float v) {
    if (u < 0.f) u = 0.f;
    else if (u > 1.f) u = 1.f;
    if (v < 0.f) v = 0.f;
    else if (v > 1.f) v = 1.f;
    auto colour = MTimage.at<cv::Vec3b>(int(u*(float)width), int((1.f-v)*(float)height));
    return Eigen::Vector3f(colour[0], colour[1], colour[2]);
}
