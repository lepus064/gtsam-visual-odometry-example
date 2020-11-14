#include "util.h"

#include <fstream>
#include <iostream>
#include <iomanip>

#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace nlohmann;
using namespace cv;

json load_config(std::string config_path) {
    std::ifstream i(config_path);
    json config;
    i >> config;
    i.close();
    return config;
}

// void load_all_frames(const nlohmann::json &config,
//                      std::vector<std::vector<cv::Mat>> &frameQue) {
//     string seq = config["data_path"].get<string>() + "/sequences/" +
//                  config["seq"].get<string>() + "/";
//     vector<string> img0_names, img1_names;
//     glob(seq + "image_0/*.png", img0_names);
//     glob(seq + "image_1/*.png", img1_names);
//     if (img0_names.size() != img1_names.size()) {
//         cout << "cam 0 != cam 1 image number" << endl;
//         return;
//     }
//     int frame_size = config["frame_size"].get<int>();
//     size_t s = img0_names.size();
//     if (frame_size != 0 && s > frame_size)
//         s = frame_size;
//     frameQue.resize(s);
//     parallel_for_(
//         Range(0, s),
//         [&](const Range &range) {
//             for (int i = range.start; i < range.end; i++) {
//                 Mat cam0 = imread(img0_names[i], 0);
//                 Mat cam1 = imread(img1_names[i], 0);
//                 frameQue[i] = {cam0, cam1};
//             }
//         },
//         2);
// }

vector<double> load_calib(const nlohmann::json &config) {
    string calib_path = config["data_path"].get<string>() + "/sequences/" +
                        config["seq"].get<string>() + "/" + "calib.txt";
    ifstream calib_data(calib_path);
    string out;
    int i = 0;
    vector<double> intrinsics(12, 0);
    calib_data >> out;
    for(auto &in:intrinsics){
        calib_data >> in;
    }
    for(const auto &in:intrinsics){
        cout << fixed << setprecision(6) <<  in << " ";
        if(++i%4 == 0)
            cout << endl;
    }
    
    return intrinsics;
}