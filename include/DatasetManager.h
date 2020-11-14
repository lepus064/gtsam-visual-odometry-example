#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <cstdint>

#include <opencv2/core.hpp>

// #include "Config.h"

class DatasetManager {

protected:
  static constexpr uint16_t bufferSize = 200;
  uint16_t currentFrameIdx = 0;
  std::thread readingThread;
  std::mutex bufferMutex;
  bool needTerminate = false;

  const uint8_t camera_number;

  // frame_cam_names[frame][cam]
  std::vector<std::vector<std::string>> frame_cam_names;

  std::queue<std::shared_ptr<std::vector<cv::Mat>>> frameBuffer;

public:
  DatasetManager(const uint8_t &cam_num, const std::vector<std::string> &cam_data_pattern);
  std::shared_ptr<std::vector<cv::Mat>> get();
  void reset();
  void stop();
  ~DatasetManager();
};