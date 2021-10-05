#include <stdio.h>
#include <iostream>
#include <string>

#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <functional>

#include <stack>
#include <map>
#include <queue>

// #include "opencv2/imgproc.hpp"
// #include "opencv2/ximgproc.hpp"
// #include "opencv2/videoio.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/video/background_segm.hpp"

// #include "uwebsockets/App.h"
#include <nlohmann/json.hpp>

#include "libs/common.h"
#include "libs/ProgramContext.cpp"
#include "libs/ProgramEventLoop.cpp"

//cmake -B build -S .
//cmake --build build

ProgramEventLoop *_programEventLoop;

int thread_main_async(int argc, char *argv[], std::string baseDir)
{

    //do background in other thread, no block current thread

    TaskJson ttest;
    ttest.jsonData = "{'xxx':'xyz'}";
    ttest.handle = [](std::string input)
    {
        //anonymous function , lambda function
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\r\nqueue_action: delay 0.5 sec to run, anonymous function , lambda function";
        std::cout << "\r\n----------jsonData: " << input << "-----------\r\n";
    };

    _programEventLoop->queue_action(ttest);

    return 0;
};

int main(int argc, char *argv[])
{
    ProgramContext::init(argc, argv);

    std::cout << "\r\nNumber of cpu = " << std::thread::hardware_concurrency() << "\r\n";

    std::cout << "baseDir: " + ProgramContext::__baseDir + "\r\n";

    _programEventLoop = new ProgramEventLoop();
    _programEventLoop->start();

    // do other thread here, use queue to do message passing between threads
    // do async
    //this is not main thread, have to use mutex or __lockGlobal if want to access variable in other thread

    std::thread thrMainAsync(thread_main_async, argc, argv, ProgramContext::__baseDir);

    std::cout << "Press 'Enter' for show menu\r\n";

    std::thread thrShowKeyboardInput(ProgramContext::thread_show_keyboardInput);

    ProgramContext::infinity_loop_read_keyboard([](std::string param)
                                                { _programEventLoop->queue_action(
                                                      TaskJson(param,
                                                               [](std::string msgOnInvoke)
                                                               {
                                                                   __log(msgOnInvoke);
                                                               })); });

    thrMainAsync.join();
    thrShowKeyboardInput.join();
    _programEventLoop->stop();
    ProgramContext::exit();
    std::cout << "\r\nGood bye! Happy coding!\r\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
};