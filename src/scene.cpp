//
// Created by wang on 2022/2/1.
//

#include "scene.h"

#include <utility>

CanaryScene::scene::scene(const std::string &rhs, int _width, int _height, float _fov, float _ratio, float zn, float zf):
config(rhs), r(_width, _height),cam_fov(_fov),aspect_ratio(_ratio),zNear(zn),zFar(zf){
    for (const auto &item:config._data_){
        r.addObject(Object(item));
        std::cout << "info>> load" << item.obj_path << " success." << std::endl;
    }
    r.setProjection(objtrans::getPerspectiveMatrix(cam_fov, aspect_ratio, zNear, zFar));
    r.setView(objtrans::getViewMatrix(CameraPos));
    r.setViewPort(objtrans::getViewPortMatrix(config.resolution.width, config.resolution.height));
}

void CanaryScene::scene::process(float angle, Eigen::Vector3f &n) {
    r.setModel(objtrans::getRotationMatrix(n, angle));
    r.process();
}

void CanaryScene::scene::process(float angle) {
    r.setModel(objtrans::getYRotationMatrix(angle));
    r.clearBuffer();
    r.process();
}

void CanaryScene::scene::addLight(light &rhs) {
    r.Light.push_back(rhs);
}

void CanaryScene::scene::changeCameraPos(Eigen::Vector3f &rhs) {
    CameraPos = rhs;
    r.CameraPos = CameraPos;
    r.setView(objtrans::getViewMatrix(CameraPos));
}
