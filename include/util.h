#pragma once

#include <string>
#include <vector>

#include <eigen3/Eigen/Core>
#include <opencv2/core.hpp>

#include "json.hpp"

nlohmann::json load_config(std::string config_path);
// void load_all_frames(const nlohmann::json &config,
//                      std::vector<std::vector<cv::Mat>> &frameQue);

// std::vector<cv::Mat> load_calib(const nlohmann::json &config);
std::vector<double> load_calib(const nlohmann::json &config);

// template <typename T>
// void reduceVector(std::vector<T> &v, std::vector<uchar> status){
//     int j = 0;
//     for (int i = 0; i < int(v.size()); i++)
//         if (status[i])
//             v[j++] = v[i];
//     v.resize(j);
// }