#pragma once

#include "json.hpp"
#include "optical_flow/OpticalFlowFrameToFrame.h"

class VO_estimator
{
private:
  /* data */
  vo::OpticalFlowFrameToFrame<float, vo::Pattern51> featureTracker;
public:
  VO_estimator(const nlohmann::json &config);
  void addFrame(const std::vector<cv::Mat> &frame);
  ~VO_estimator();
};

