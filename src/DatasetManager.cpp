#include "DatasetManager.h"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;

DatasetManager::DatasetManager(const uint8_t &cam_num, const std::vector<std::string> &cam_data_pattern)
    : camera_number(cam_num) {
  
  vector<vector<string>> cam_i_names(camera_number);
  for (int cam = 0; cam < camera_number; cam++) {
    cv::glob(cam_data_pattern[cam], cam_i_names[cam]);
  }
  frame_cam_names.resize(cam_i_names[0].size());
  for (size_t frame = 0; frame < frame_cam_names.size(); frame++) {
    vector<string> cam_name_in_frame(cam_i_names.size());
    for (size_t cam = 0; cam < cam_i_names.size(); cam++) {
      cam_name_in_frame[cam] = cam_i_names[cam][frame];
    }
    frame_cam_names[frame] = cam_name_in_frame;
  }

  // if (config.datasetType() == "EuRoC") {
  //   string datasetDirPrefix = config.datasetDir() + "/mav0/cam";
  //   vector<vector<string>> cam_i_names(camera_number);
  //   for (int cam = 0; cam < camera_number; cam++) {
  //     cv::glob(datasetDirPrefix + to_string(cam) + "/data/*.png",
  //              cam_i_names[cam]);
  //   }
  // } else {
  //   cout << "b" << endl;
  // }
  reset();
}

std::shared_ptr<std::vector<cv::Mat>> DatasetManager::get() {
  while (frameBuffer.empty()) {
    this_thread::sleep_for(chrono::milliseconds(50));
  }
  auto frame = frameBuffer.front();
  if (frame != nullptr) {
    frameBuffer.pop();
  }
  return frame;
}

void DatasetManager::reset() {
  needTerminate = true;
  if (readingThread.joinable()) {
    readingThread.join();
  }
  while (!frameBuffer.empty()) {
    frameBuffer.pop();
  }

  needTerminate = false;
  currentFrameIdx = 0;
  readingThread = std::thread([&]() {
    while (!needTerminate && currentFrameIdx < frame_cam_names.size()) {
      if (frameBuffer.size() < bufferSize) {
        vector<cv::Mat> frame_i(camera_number);
        for (int cam = 0; cam < camera_number; cam++) {
          frame_i[cam] = cv::imread(frame_cam_names[currentFrameIdx][cam],
                                    cv::IMREAD_UNCHANGED);
        }
        frameBuffer.push(make_shared<vector<cv::Mat>>(frame_i));
        currentFrameIdx++;
      } else {
        this_thread::sleep_for(chrono::milliseconds(5));
      }
    }
    frameBuffer.push(nullptr);
  });
}

void DatasetManager::stop(){
  needTerminate = true;
  if (readingThread.joinable()) {
    readingThread.join();
  }
  while (!frameBuffer.empty()) {
    frameBuffer.pop();
  }
}

DatasetManager::~DatasetManager() {
  if (readingThread.joinable())
    readingThread.join();
}