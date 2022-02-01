//
// Created by wang on 2022/2/1.
//

#ifndef CANARYRENDER_CFG_PHASER_H
#define CANARYRENDER_CFG_PHASER_H
#include <vector>
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
namespace CanaryPhaser{
    typedef struct {
        /* struct of object storage path in option.txt, only support .obj file.
         * For texture, only basic <rgb texture> and <high map> are supported,
         * .jpg/.png are both supported. You can add more texture type for this
         * project. Maybe this option phaser method is shabby, however, a json
         * lib is over-weighted for this project.(too lazy to use it:actually)
         *
         * tex_map for basic rgb shader, high_map for bump and displacement texture.
         */
        std::string obj_path;
        std::string tex_map, high_map;
    }objCfgNode;

    typedef struct {
        int width, height;
    }CfgResolution;

    class option{
        /* This class phase option from a txt file.
         * Pass every 3D object value by an objCfgNode struct.
         */
    public:
        option() = delete;
        explicit option(const std::string &rhs) { _phaser_(rhs);}
        CfgResolution resolution{};
        std::vector<objCfgNode> _data_;
        void print() const;

    private:
        void _phaser_(const std::string &rhs);
    };
}

#endif //CANARYRENDER_CFG_PHASER_H
