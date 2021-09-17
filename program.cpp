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
//#include "libs/httpserver.h"

using namespace std;
using namespace cv;
using namespace Human;

// void get_handler(uws_res_t *res, uws_req_t *req) {
//     uws_res_end(res, "Hello CAPI!", 11);
// }

// void listen_handler(void *listen_socket) {
//     if (listen_socket) {
//         printf("Listening on port now\n");
//     }
// }

int main(int argc, char *argv[])
{
    cout << "Hello world\r\n";
    
    Human::Man * me = new Man();
    me->sayHello();

    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));

    cout << "baseDir: " + baseDir + "\r\n";

    std::string strFromChar;

    Mat img = imread(baseDir + "/1.png", IMREAD_GRAYSCALE);
    //Mat img = imread("/home/dunp/work/cmakes-helloworld/1.png", IMREAD_GRAYSCALE);
    
    Mat dst;

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    dst = Mat::zeros(img.size(), CV_8UC3);
    if (contours.size() == 0)
        return 0;
    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0, largestComp = 0;
    double maxArea = 0;
    for (; idx >= 0; idx = hierarchy[idx][0])
    {
        const vector<Point> &c = contours[idx];
        double area = fabs(contourArea(Mat(c)));
        if (area > maxArea)
        {
            maxArea = area;
            largestComp = idx;
        }
    }
    Scalar color(0, 0, 255);

    drawContours(dst, contours, largestComp, color, FILLED, LINE_8, hierarchy);

    //imshow("dst",dst);
    //char keycode = (char)waitKey(0);
    
    // uws_app_t *app = uws_create_app();
    // uws_app_get(app, "/*", get_handler);
    // uws_app_listen(app, 3000, listen_handler);
    // uws_app_run(app);

    while (true)
    {
        // current date/time based on current system
        time_t now = time(0);

        // convert now to string form
        char *dt = ctime(&now);

        cout << "The local date and time is: " << dt << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
