#include "src/scene.h"
#include "omp.h"
int main() {
    omp_set_num_threads(4);
    std::cout << "Start simulation" << std::endl;
    CanaryScene::scene sce(R"(D:\Project\CanaryRender\ModelZoo\spot\option.txt)",
                                                     700, 700,45.f, 1.f, 0.1f, 50.f);
    Eigen::Vector3f camera_pos({0,0,10});
    light l1{{20,20,20}, {500,500,500}}, l2{{-20, 20, 0},{500,500,500}};
    sce.addLight(l1);
    sce.addLight(l2);
    sce.changeCameraPos(camera_pos);
    std::function<Eigen::Vector3f(FragmentShaderUnit)> main_shader = MShader::TexturePhongFragmentFhader;
    sce.r.setFragmentShader(main_shader);
    int key = 0;
    float angle = 100.f;
    while(key!=27){
        sce.process(angle);
        cv::Mat image(700, 700, CV_32FC3, sce.r.frame().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        cv::imshow("Image", image);
        key = cv::waitKey(1);
        if (key == 'a' ){ angle -= 0.5;}
        else if (key == 'd'){ angle += 0.5;}
    }
    return 0;
    // cv::imwrite(R"(D:\Project\CanaryRender\tmp\bunny.png)", image);
}
