//
// Created by wang on 2022/2/1.
//

#include "shader.h"

void FragmentShaderUnit::setViewPos(const Eigen::Vector3f &rhs) {
    viewPos = rhs;
}

Eigen::Vector3f MShader::TexturePhongFragmentFhader(const FragmentShaderUnit &rhs){
    Eigen::Vector3f tmp = {0, 0, 0};
    if (rhs.texture != nullptr){
        tmp = rhs.texture->colorAt(rhs.textureUV.x(), rhs.textureUV.y());
    }
    Eigen::Vector3f texture_color;
    texture_color << tmp.x(), tmp.y(), tmp.z();
    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f kd = texture_color / 255.f;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);
    Eigen::Vector3f amb_light_intensity{10, 10, 10};
    Eigen::Vector3f color = texture_color;
    Eigen::Vector3f point = rhs.viewPos;
    Eigen::Vector3f normal = rhs.normal;
    Eigen::Vector3f res = {0, 0, 0};
    Eigen::Vector3f viewDir = (-point).normalized();
    float p = 150.f;
    for (const auto& light:rhs._light){
        Eigen::Vector3f lightDir = (light.position - point).normalized();
        Eigen::Vector3f halfDir = ((lightDir + viewDir) / 2.0f).normalized();
        float r2 = (light.position - point).squaredNorm();
        auto ambient = ka.cwiseProduct(amb_light_intensity);
        auto diffuse = kd.cwiseProduct(light.intensity / r2 * MAX(0.0f, normal.dot(lightDir)));
        auto specular = ks.cwiseProduct(light.intensity / r2 * std::pow(MAX(0.0f, normal.dot(halfDir)), p));
        res += ambient + diffuse + specular;
    }
    return res*255.f;
}

Eigen::Vector3f MShader::PhongFragmentSahder(const FragmentShaderUnit &rhs){
    Eigen::Vector3f ka = Eigen::Vector3f(0.005, 0.005, 0.005);
    Eigen::Vector3f amb_light_intensity{10, 10, 10};
    Eigen::Vector3f kd = rhs.colour;
    Eigen::Vector3f ks = Eigen::Vector3f(0.7937, 0.7937, 0.7937);
    Eigen::Vector3f color = rhs.colour;
    Eigen::Vector3f point = rhs.viewPos;
    Eigen::Vector3f normal = rhs.normal;
    Eigen::Vector3f res = {0, 0, 0};
    Eigen::Vector3f viewDir = (-point).normalized();
    float p = 150.f;
    for (const auto& light:rhs._light){
        Eigen::Vector3f lightDir = (light.position - point).normalized();
        Eigen::Vector3f halfDir = ((lightDir + viewDir) / 2.0f).normalized();
        float r2 = (light.position - point).squaredNorm();
        auto ambient = ka.cwiseProduct(amb_light_intensity);
        auto diffuse = kd.cwiseProduct(light.intensity / r2 * MAX(0.0f, normal.dot(lightDir)));
        auto specular = ks.cwiseProduct(light.intensity / r2 * std::pow(MAX(0.0f, normal.dot(halfDir)), p));
        res += ambient + diffuse + specular;
    }
    return res*255.f;
}
