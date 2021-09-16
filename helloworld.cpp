#include <stdio.h>
#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video/background_segm.hpp"

using namespace std;
using namespace cv;

int main(int argc, char *argv[]){
    cout << "Hello world\r\n";

    std::string argv_str(argv[0]);
    std::replace(argv_str.begin(),argv_str.end(),'\\','/');
    std::string baseDir = argv_str.substr(0, argv_str.find_last_of("/"));

    cout << "baseDir: "+ baseDir+"\r\n";

    std::string strFromChar;

    Mat img = imread(baseDir+"/1.png", IMREAD_GRAYSCALE);
    //Mat img = imread("/home/dunp/work/cmakes-helloworld/1.png", IMREAD_GRAYSCALE);
    Mat dst;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    findContours( img, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE );
    
    dst = Mat::zeros(img.size(), CV_8UC3);
    if( contours.size() == 0 )
        return 0;
    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0, largestComp = 0;
    double maxArea = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        const vector<Point>& c = contours[idx];
        double area = fabs(contourArea(Mat(c)));
        if( area > maxArea )
        {
            maxArea = area;
            largestComp = idx;
        }
    }
    Scalar color( 0, 0, 255 );

    drawContours( dst, contours, largestComp, color, FILLED, LINE_8, hierarchy );

    imshow("dst",dst);
    char keycode = (char)waitKey(0);
}
