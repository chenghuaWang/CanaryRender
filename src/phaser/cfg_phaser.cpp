//
// Created by wang on 2022/2/1.
//

#include "cfg_phaser.h"

inline void CanaryPhaser::option::_phaser_(const std::string &rhs) {
    size_t len = 0;
    std::ifstream buf_file(rhs);
    std::string str_buf;
    buf_file >> str_buf;
    if (str_buf == ".scene"){
        buf_file >> resolution.width >> resolution.height;
    }
    else { exit(1);}
    buf_file >> str_buf;
    if (str_buf == ".object"){
        while(std::getline(buf_file, str_buf)){
            std::regex ws_re("\\s+");
            std::vector<std::string> res(std::sregex_token_iterator(str_buf.begin(), str_buf.end(), ws_re, -1),
                                         std::sregex_token_iterator());
            len = res.size();
            if (len==1) {_data_.push_back(objCfgNode{res[0], "", ""});}
            else if (len==2) {_data_.push_back(objCfgNode{res[0], res[1], ""});}
            else if (len==3) {_data_.push_back(objCfgNode{res[0], res[1], res[2]});}
            std::cout << "info>> Phased " << len << " objects." << std::endl;
        }
    }
    else{ exit(1);}
}

inline void CanaryPhaser::option::print() const {
    std::cout << "<scene>" << resolution.width << "x" << resolution.height << std::endl;
    std::cout << "<object>" << std::endl;
    for (const auto& item:_data_){
        std::cout << "object:" << item.obj_path << ",";
        std::cout << "texture:" << item.tex_map << ",";
        std::cout << "high-map:" << item.high_map << std::endl;
    }
}
