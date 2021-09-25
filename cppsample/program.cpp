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

#ifdef _WIN32

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>

#include <curses.h>
//./vcpkg install ncurses
//sudo apt-get install libncurses5-dev libncursesw5-dev
//sudo yum install ncurses-devel ncurses
#endif

// #include "opencv2/imgproc.hpp"
// #include "opencv2/ximgproc.hpp"
// #include "opencv2/videoio.hpp"
// #include "opencv2/highgui.hpp"
// #include "opencv2/video/background_segm.hpp"

// #include "uwebsockets/App.h"
// #include <nlohmann/json.hpp>

#include "libs/common.h"
#include "libs/common.h"
#include "libs/ProgramEventLoop.cpp"

//cmake -B build -S .
//cmake --build build

std::mutex __lockGlobal;
//thread safe with lock for queue
std::queue<int> __qKeyboardInput;
std::stack<int> __stackTest;
std::map<std::string, std::string> __mapTest;

ProgramEventLoop *_programEventLoop;

bool __stop;
int quit()
{
    if (__lockGlobal.try_lock())
    {
        __stop = true;
        __lockGlobal.unlock();
    }
    return 0;
}

int thread_show_keyboardInput()
{
    size_t qsize = 0;

    while (true)
    {
        if (__stop)
        {
            break;
        }
        char c = NULL;
        if (__lockGlobal.try_lock())
        {
            qsize = __qKeyboardInput.size();
            if (qsize > 0)
            {
                c = __qKeyboardInput.front();
                __qKeyboardInput.pop();
                qsize = qsize - 1;

                //__stackTest.top();
                //__stackTest.pop();
            }

            __lockGlobal.unlock();
        }

        if (c != NULL)
        {
            std::cout << "\r\n char: " << (char)c << " ascii: " << (int)c << ": Pressed, " << qsize << ": remain in queue, press Enter key for menu\r\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}

int thread_main_async(int argc, char *argv[], std::string baseDir)
{
    int var = 20; // actual variable declaration.
    int *ip;      // pointer variable

    ip = &var; // store address of var in pointer variable

    std::cout << "Value of var variable: ";
    std::cout << var << std::endl;

    // print the address stored in ip pointer variable
    std::cout << "Address stored in ip variable: ";
    std::cout << ip << std::endl;

    // access the value at the address available in pointer
    std::cout << "Value of *ip variable: ";
    std::cout << *ip << std::endl;

    // assign var with new value
    *ip = 50;
    std::cout << "New value assigned *ip = 50; Address stored in ip variable: ";
    std::cout << ip << std::endl;

    std::cout << "New Value of var variable: ";
    std::cout << var << std::endl;

    std::cout << "&ip: ";
    std::cout << &ip << std::endl;
    std::cout << "*ip: ";
    std::cout << *ip << std::endl;
    
    std::cout << "&var: ";
    std::cout << &var << std::endl;
    
    ///end testpointer

    //this is not main thread, have to use mutex or __lockGlobal if want to access variable in other thread
    std::cout << "\r\nNumber of threads = " << std::thread::hardware_concurrency() << "\r\n";

    std::cout << "baseDir: " + baseDir + "\r\n";
    __mapTest["baseDir"] = baseDir;

    //do background in other thread, no block current thread
    _programEventLoop->queue_action(
        []()
        {
            //anonymous function , lambda function
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "\r\nqueue_action: delay 0.5 sec to run, anonymous function , lambda function\r\n";

            //test use map
            //todo: may lack here cause thread may not safe, __mapTest assign key baseDir in thread thread_main_async, but queue_action will run in thread thrEventLoop(thread_queue_action_invoke)

            auto find = __mapTest.find("baseDir");
            if (find != __mapTest.end())
                std::cout << "\r\nmap Found: " << find->first << ": " << find->second << "\r\n";
        });

    return 0;
}

int main(int argc, char *argv[])
{
    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));
    __stop = false;

    _programEventLoop = new ProgramEventLoop();
    _programEventLoop->start();

    // do other thread here, use queue to do message passing between threads
    // do async

    std::thread thrMainAsync(thread_main_async, argc, argv, baseDir);

    std::cout << "Press Enter then type 'q' key to quit\r\n";

    std::thread thrShowKeyboardInput(thread_show_keyboardInput);

    while (true)
    {
        if (__stop)
        {
            break;
        }
        // prevent close main thread
        // to run services as single thread (main thread)
        // event loop services using queue to do message transfer

        if (_kbhit() != 0)
        {
            //read any key input from keyboard
            int input = _getch();
            if (__lockGlobal.try_lock())
            {
                __qKeyboardInput.push(input);
                __stackTest.push(input);
                __lockGlobal.unlock();
            }
            //if(input==32) break; //space pressed
            if (input == 13)
            {
                std::cout << "\r\nPress 'q' key to quit\r\n";
                std::cout << "Press 'a' key to call _programEventLoop->queue_action\r\n";

                int q = _getch();

                if (q == (int)'q')
                {
                    if (__lockGlobal.try_lock())
                    {
                        __stop = true;
                        __lockGlobal.unlock();
                    }
                }
                if (q == (int)'a')
                {
                    _programEventLoop->queue_action(
                        []()
                        {
                            time_t now = time(0);
                            char *dt = ctime(&now);
                            std::cout << "\r\n_programEventLoop->queue_action called at: " << dt << "\r\n";
                        });
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    thrMainAsync.join();
    thrShowKeyboardInput.join();
    _programEventLoop->stop();

    std::cout << "\r\nGood bye! Happy coding!\r\n";

    return 0;
}