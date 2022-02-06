//
// Created by wang on 2022/2/6.
//

#include "Ray.h"

Vector3f Ray::operator()(float t) {
    return Eigen::Vector3f(ori + des * t);
}
