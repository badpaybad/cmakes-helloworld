#include <stdio.h>
#include <iostream>
#include <string>

#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>

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
bool __stop;

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

int main()
{
    __stop = false;

    std::cout << "Press Enter then type 'q' key to quit\r\n";

    std::thread thrShowKeyboardInput(thread_show_keyboardInput);

    // do other thread here, use queue to do message passing between threads
    // do async

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

    thrShowKeyboardInput.join();

    std::cout << "\r\nGood bye! Happy coding!\r\n";
}