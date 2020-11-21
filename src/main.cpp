#include <iostream>
#include <opencv2/highgui.hpp>
#include "util.h"
#include "DatasetManager.h"
#include "VO_estimator.h"

using namespace std;
int main(){
  auto config = load_config("../data/kitti.json");
  vector<string> data_pattern(2);
  data_pattern[0] = config["data_path"].get<string>()+"/"+ config["seq"].get<string>() + "/image_0/*.png";
  data_pattern[1] = config["data_path"].get<string>()+"/"+ config["seq"].get<string>() + "/image_1/*.png";

  DatasetManager dm(2, data_pattern);

  VO_estimator vo_estimator(config);


  while(true){
    auto frame_ptr = dm.get();
    if(frame_ptr == nullptr)
      break;
    vo_estimator.addFrame(*frame_ptr);
    // featureTracker.processFrame(*frame_ptr);
    // cv::Mat f;
    // cv::vconcat((*frame)[0], (*frame)[1], f);
    // cv::imshow("cam0", f);
  }
  return 0;
}