// Author : Daniel Xie
// Class for streaming video from a camera or file with Gstreamer as a multi threaded process
// functions:
//  - check if pipeline is up
//  - get frame from pipeline
//  - preview frame from pipeline
//  - set grayscale or RGB
//  - set camera mode

#ifndef __RGBCAMERA_HPP__
#define __RGBCAMERA_HPP__

#define GRAYSCALE "NV12"
#define RGB "BGRx"

#include <opencv2/core/core.hpp>
#include <opencv2/videoio.hpp>
#include <rclcpp/rclcpp.hpp>
#include <map>

using namespace std;

enum CameraMode {
    MODE_0,
    MODE_1,
    MODE_2,
    MODE_3,
    MODE_4
};

struct CameraConfig {
    int mode;
    string width;
    string height;
    string framerate;
};

struct RGBFrame {
    cv::Mat frame;
    rclcpp::Time timestamp;
};

extern std::map<CameraMode, CameraConfig> cameraConfigs;


class RGBCamera
{
    // pipeline: "nvarguscamerasrc sensor-mode=2 ! video/x-raw(memory:NVMM),width=1920,height=1080,format=(string)NV12,framerate=(fraction)30/1 ! "
    //           "nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! videoflip method=rotate-180  ! appsink"

    public:
        RGBCamera(bool isColor, CameraMode mode, bool vflip);
        RGBCamera();
        ~RGBCamera();

        bool isOpened() const;
        RGBFrame getFrame();
        void setPipeline();
        RGBFrame image;

    private:
        bool isColor;
        CameraMode mode;
        cv::VideoCapture cap;
        std::string pipeline;
        bool vflip;
};

#endif