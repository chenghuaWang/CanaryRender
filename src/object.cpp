//
// Created by wang on 2022/2/1.
//

#include "object.h"

Object::~Object() {
    delete texture;
    delete high_map;
}

Object::Object(const CanaryPhaser::objCfgNode &rhs) {
    if (!rhs.tex_map.empty()) texture = new MTexture(rhs.tex_map);
    if (!rhs.high_map.empty()) high_map = new MTexture(rhs.high_map);
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(rhs.obj_path);
    if (loadout){
        for (const auto& mesh:Loader.LoadedMeshes){
            for (int i = 0; i < mesh.Vertices.size(); i+=3) {
                auto *tmp = new Triangle();
                for (int j = 0; j < 3; ++j) {
                    tmp->setVertex(j,Eigen::Vector4f(mesh.Vertices[i+j].Position.X,mesh.Vertices[i+j].Position.Y,mesh.Vertices[i+j].Position.Z,1.0));
                    tmp->setNormal(j,Eigen::Vector3f(mesh.Vertices[i+j].Normal.X,mesh.Vertices[i+j].Normal.Y,mesh.Vertices[i+j].Normal.Z));
                    tmp->setTextureUV(j,Eigen::Vector2f(mesh.Vertices[i+j].TextureCoordinate.X, mesh.Vertices[i+j].TextureCoordinate.Y));
                }
                TriangleList.push_back(tmp);
            }
        }
    }else{
        std::cout << "Error>> Load Object: " << rhs.obj_path << " failed!" << std::endl;
        exit(1);
    }
}

