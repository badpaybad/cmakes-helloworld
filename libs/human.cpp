#include "human.h"
// #include "opencv2/imgproc.hpp"
// #include "opencv2/videoio.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/video/background_segm.hpp"

namespace Human
{
    void Man::sayHello()
    {
        std::cout << "Hello, I am man!\n";
    }

    /**
     * @brief
     *
     * @param baseDir dir where file exec int main()
     */
    void Man::testOpenCv(std::string baseDir)
    {
        // cv::Mat img = cv::imread(baseDir + "/1.png", cv::IMREAD_GRAYSCALE);
        std::cout << "Just remove to easy demo Dockerfile";
    }

    void Woman::sayHello()
    {
        std::cout << "Hello, I am woman!\n";
    }
    void Other::sayHello()
    {
        std::cout << "Hello, I am other!\n";
    }
}