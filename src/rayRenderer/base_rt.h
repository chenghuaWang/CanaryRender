//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_BASE_RT_H
#define CANARYRENDER_BASE_RT_H

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#ifdef _MSC_VER
typedef signed char int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <inttypes.h>
#endif

#define openmp_enable true

#define Canary_PI 3.14159265359f
#include <Eigen/Eigen>

#include "../phaser/OBJ_Loader.h"

#endif //CANARYRENDER_BASE_RT_H
