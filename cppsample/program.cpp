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
#include <queue>;

#ifdef _WIN32

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>

#include <curses.h>
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

//cmake -B build -S .
//cmake --build build

std::mutex __lockGlobal;
//thread safe with lock for queue
std::queue<int> __qKeyboardInput;
std::stack<int> __stackTest;
std::map<std::string, std::string> __mapTest;

std::mutex __lockEventLoop;
std::queue<std::function<void()>> __qVoid;

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

int queue_action(std::function<void()> a)
{
    if (__lockEventLoop.try_lock())
    {
        __qVoid.push(a);
        __lockEventLoop.unlock();
    }

    return 0;
}
int thread_queue_action_invoke(std::string baseDir)
{
    std::function<void()> a = NULL;

    while (true)
    {
        if (__stop)
        {
            break;
        }

        if (__lockEventLoop.try_lock())
        {
            if (__qVoid.size() > 0)
            {
                a = __qVoid.front();
                __qVoid.pop();
            }
            __lockEventLoop.unlock();
        }

        if (a != NULL)
        {
            a();
            a = NULL;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }

    return 0;
}

int thread_show_keyboardInput()
{
    int qsize = 0;

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
            std::cout << "\r\n char: " << (char)c << " ascii: " << (int)c << ": Pressed, " << qsize << ": remain in queue\r\n";
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}

int thread_main_async(int argc, char *argv[], std::string baseDir)
{
    //this is not main thread, have to use mutex or __lockGlobal if want to access variable in other thread

    std::cout << "baseDir: " + baseDir + "\r\n";
    __mapTest["baseDir"] = baseDir;

    //do background in other thread, no block current thread
    queue_action(
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
    __stop = false;

    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));

    std::cout << "Press Enter then type 'q' key to quit\r\n";

    std::thread thrShowKeyboardInput(thread_show_keyboardInput);

    // do other thread here, use queue to do message passing between threads
    // do async

    std::thread thrMainAsync(thread_main_async, argc, argv, baseDir);

    std::thread thrEventLoop(thread_queue_action_invoke, baseDir);

    while (true)
    {
        if (__stop)
        {
            break;
        }
        // prevent close main thread
        // to run services as single thread (main thread)
        // event loop services using queue to do message transfer

        if (kbhit() != 0)
        {
            //read any key input from keyboard
            int input = getch();
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

                char q = getch();
                if (q == 'q')
                {
                    if (__lockGlobal.try_lock())
                    {
                        __stop = true;
                        __lockGlobal.unlock();
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    thrEventLoop.join();
    thrMainAsync.join();
    thrShowKeyboardInput.join();

    std::cout << "\r\nGood bye! Happy coding!\r\n";

    return 0;
}