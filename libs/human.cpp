#include "human.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video/background_segm.hpp"

using namespace std;
using namespace cv;

namespace Human {
  void Man::sayHello() {
    cout << "Hello, I am man!\n";    
  }

  void Man::testOpenCv(std::string baseDir){    
      Mat img = imread(baseDir + "/1.png", IMREAD_GRAYSCALE);
  }

  void Woman::sayHello() {
    cout << "Hello, I am woman!\n";
  }
  void Other::sayHello() {
    cout << "Hello, I am other!\n";
  }
}