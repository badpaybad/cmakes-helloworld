#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <thread>

#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video/background_segm.hpp"

#include "libs/human.h"
#include "libs/httpserver.h"
#include "uwebsockets/App.h"
#include <nlohmann/json.hpp>

#include "opencv2/imgproc.hpp"
#include "opencv2/ximgproc.hpp"
#include "opencv2/videoio.hpp"
#include <conio.h>
using namespace Human;

// //begin#httpserver#

int __port = 9004;

#ifdef __cplusplus
extern "C"
{
#endif
    void get_handler(uws_res_t *res, uws_req_t *req)
    {
        uws_res_end(res, "Hello world! I am Du", 11);
    }
    void get_handler_about(uws_res_t *res, uws_req_t *req)
    {
        auto j3 = nlohmann::json::parse(R"({"name": "nguyen phan du","nlohmann": "https://github.com/nlohmann/json", "json":true, "version":1})");

        //uws_res_end(res, "{'name':'nguyen phan du'}", 11);
        auto about = j3.dump();
        auto aboutC = about.c_str();
        uws_res_end(res, aboutC, strlen(aboutC));
    }
    void listen_handler(void *listen_socket)
    {
        if (listen_socket)
        {
            printf("Listening on port: %d\r\n", __port);
        }
    }

#ifdef __cplusplus
}
#endif
// //end#httpserver#

int main(int argc, char *argv[])
{

    std::cout << "Hello world! I am Du\r\n";
    
    // while (true)
    // {
    //     if (kbhit() != 0)
    //     {//read any key input from keyboard
    //         int input = getch();            
    //         if(input==32) break;
    //     }
    // }

    Human::Man *me = new Man();
    me->sayHello();

    int length_threshold = 10;
    float distance_threshold = 1.41421356f;
    double canny_th1 = 50.0;
    double canny_th2 = 50.0;
    int canny_aperture_size = 3;
    bool do_merge = false;

    cv::Ptr<cv::ximgproc::FastLineDetector> fld = cv::ximgproc::createFastLineDetector(length_threshold,
                                                                                       distance_threshold, canny_th1, canny_th2, canny_aperture_size,
                                                                                       do_merge);

    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));

    std::cout << "baseDir: " + baseDir + "\r\n";

    std::string strFromChar;

    cv::Mat img = cv::imread(baseDir + "/1.png", cv::IMREAD_GRAYSCALE);
    //Mat img = imread("/home/dunp/work/cmakes-helloworld/1.png", IMREAD_GRAYSCALE);

    cv::Mat dst;

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    findContours(img, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

    dst = cv::Mat::zeros(img.size(), CV_8UC3);
    if (contours.size() == 0)
        return 0;
    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0, largestComp = 0;
    double maxArea = 0;
    for (; idx >= 0; idx = hierarchy[idx][0])
    {
        const std::vector<cv::Point> &c = contours[idx];
        double area = fabs(cv::contourArea(cv::Mat(c)));
        if (area > maxArea)
        {
            maxArea = area;
            largestComp = idx;
        }
    }
    cv::Scalar color(0, 0, 255);

    drawContours(dst, contours, largestComp, color, cv::FILLED, cv::LINE_8, hierarchy);

    // imshow("dst",dst);
    // char keycode = (char)cv::waitKey(0);

    uws_app_t *app = uws_create_app();
    //register routing:
    uws_app_get(app, "/", get_handler);
    uws_app_get(app, "/about", get_handler_about);

    //start httpserver then block main thread
    uws_app_listen(app, __port, listen_handler);
    uws_app_run(app);

    while (true)
    {
        // current date/time based on current system
        time_t now = time(0);

        // convert now to string form
        char *dt = ctime(&now);

        std::cout << "The local date and time is: " << dt << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
