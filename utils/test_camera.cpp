#include "../include/RGBCamera.hpp"
#include <opencv4/opencv2/opencv.hpp>

using namespace std;

int main(int argc, char** argv)
{
    RGBCamera rgb_camera(true, MODE_2, true);

    if (!rgb_camera.isOpened())
    {
        cout << "RGBCamera failed to open" << endl;
        return -1;
    }

    while (1)
    {
        RGBFrame img = rgb_camera.getFrame();

        if (img.frame.empty())
        {
            cout << "Frame is empty" << endl;
            break;
        }

        cv::imshow("Frame", img.frame);
        int key = cv::waitKey(1);

        if (key == 'q')
        {
            break;
        }
    }
    
    cv::destroyAllWindows();
    return 0;
}