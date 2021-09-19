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
#include "uwebsockets/App.h"

using namespace Human;

#ifndef HTTSERVER_DEF_HEADER
    #define HTTSERVER_DEF_HEADER
 
    #ifdef __cplusplus
    extern "C" {
    #endif         
    
        #include <stddef.h>   
        struct uws_app_s;
        struct uws_req_s;
        struct uws_res_s;
        typedef struct uws_app_s uws_app_t;
        typedef struct uws_req_s uws_req_t;
        typedef struct uws_res_s uws_res_t;

        uws_app_t *uws_create_app();
        void uws_app_get(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *));
        void uws_app_run(uws_app_t *);

        void uws_app_listen(uws_app_t *app, int port, void (*handler)(void *));

        void uws_res_end(uws_res_t *res, const char *data, size_t length);

     
    #ifdef __cplusplus
    }
    #endif

#endif

     
    uws_app_t *uws_create_app() {
        return (uws_app_t *) new uWS::App();
    }

    void uws_app_get(uws_app_t *app, const char *pattern, void (*handler)(uws_res_t *, uws_req_t *)) {
        uWS::App *uwsApp = (uWS::App *) app;
        uwsApp->get(pattern, [handler](auto *res, auto *req) {
            handler((uws_res_t *) res, (uws_req_t *) req);
        });
    }

    void uws_app_run(uws_app_t *app) {
        uWS::App *uwsApp = (uWS::App *) app;
        uwsApp->run();
        
        std::cout << "HttpServerStarted\r\n";
    }

    void uws_res_end(uws_res_t *res, const char *data, size_t length) {
        uWS::HttpResponse<false> *uwsRes = (uWS::HttpResponse<false> *) res;
        //uwsRes->end(data, length);
        uwsRes->end(data);
    }

    void uws_app_listen(uws_app_t *app, int port, void (*handler)(void *)) {
        uWS::App *uwsApp = (uWS::App *) app;
        uwsApp->listen(port, [handler](struct us_listen_socket_t *listen_socket) {
            handler((void *) listen_socket);
        });
    }
    


void get_handler(uws_res_t *res, uws_req_t *req) {
    uws_res_end(res, "Hello world!", 11);
}

void listen_handler(void *listen_socket) {
    if (listen_socket) {
        printf("Listening on port now\n");
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Hello world\r\n";
    
    Human::Man * me = new Man();
    me->sayHello();

    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));

    std::cout << "baseDir: " + baseDir + "\r\n";

    std::string strFromChar;

    cv::Mat img = cv::imread(baseDir + "/1.png", cv::IMREAD_GRAYSCALE);
    //Mat img = imread("/home/dunp/work/cmakes-helloworld/1.png", IMREAD_GRAYSCALE);
    
    cv::Mat dst;

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;

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
        const vector<cv::Point> &c = contours[idx];
        double area = fabs(cv::contourArea(cv::Mat(c)));
        if (area > maxArea)
        {
            maxArea = area;
            largestComp = idx;
        }
    }
    cv::Scalar color(0, 0, 255);

    drawContours(dst, contours, largestComp, color, cv::FILLED, cv::LINE_8, hierarchy);

    //imshow("dst",dst);
    //char keycode = (char)waitKey(0);
    
    uws_app_t *app = uws_create_app();
    uws_app_get(app, "/*", get_handler);
    uws_app_listen(app, 9004, listen_handler);
    uws_app_run(app);

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
