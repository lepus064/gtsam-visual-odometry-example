#include "VO_estimator.h"
#include "util.h"


using namespace std;

VO_estimator::VO_estimator(const nlohmann::json &config)
{  
  Sophus::SE3f T_1_0;
  T_1_0.translation().x() = -386.1448;
  auto calib = load_calib(config);
  Eigen::Matrix3f intrinsic;
  intrinsic << calib[0], calib[1], calib[2], calib[4], calib[5], calib[6], calib[8], calib[9], calib[10];
  cout << intrinsic << endl;
  featureTracker = vo::OpticalFlowFrameToFrame<float, vo::Pattern51>(2, T_1_0);
}

void VO_estimator::addFrame(const std::vector<cv::Mat> &frame){
  featureTracker.processFrame(frame);
}

VO_estimator::~VO_estimator()
{
}