#include <iostream>
#include <opencv2/highgui.hpp>
#include "util.h"
#include "DatasetManager.h"

using namespace std;
int main(){
  cout << "hello" << endl;
  auto config = load_config("../data/kitti.json");
  vector<string> data_pattern(2);
  data_pattern[0] = config["data_path"].get<string>()+"/"+ config["seq"].get<string>() + "/image_0/*.png";
  data_pattern[1] = config["data_path"].get<string>()+"/"+ config["seq"].get<string>() + "/image_1/*.png";
  cout << data_pattern[0] << endl;
  DatasetManager dm(2, data_pattern);
  while(true){
    auto frame = dm.get();
    if(frame == nullptr)
      break;
    cv::Mat f;
    cv::vconcat((*frame)[0], (*frame)[1], f);
    cv::imshow("cam0", f);
    cv::waitKey(30);
  }
  return 0;
}