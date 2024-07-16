#include "video_control.h"

#include <sys/stat.h>

#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>

std::string GetCurrentTime();

int main(const int argc, const char **argv) {
	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " <camera_id> <output_directory>" << std::endl;
		return 1;
	}
	
	const unsigned char kCameraId = std::atoi(argv[1]);
	const std::string kOutputDirectory = argv[2];
	
	// Create the output directory if it doesn't exist
	if (mkdir(kOutputDirectory.c_str(), 0777) == 0) {
		std::cout << "Output directory created: " << kOutputDirectory << std::endl;
	}	

	cv::VideoCapture capture(kCameraId);
	
	if (!capture.isOpened()) {
		std::cerr << std::endl << "can't open camera: " << (int)kCameraId << std::endl;
		return 1;
	} else {
		const int fourcc = cv::VideoWriter::fourcc('M','J','P','G');
		capture.set(cv::CAP_PROP_FOURCC, fourcc);
		capture.set(cv::CAP_PROP_FPS, 30);
		capture.set(cv::CAP_PROP_FRAME_WIDTH, 640);
		capture.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	}
	
	cv::namedWindow("frame", cv::WINDOW_AUTOSIZE);
	
	cv::Mat frame;
	v4l2::VideoControl video_control("config.yaml", kCameraId);
	
	const char kEscape = 27;
	const char kSaveFrame = 's';
	const char kWriteConfig = 'w';
	char key = 0;
	
	while (key != kEscape) {
		key = cv::waitKey(1);
		if (key == kSaveFrame) {
			std::string filename = kOutputDirectory + "/frame_" + GetCurrentTime() + ".jpg";
			cv::imwrite(filename, frame);
			std::cout << "Frame saved as: " << filename << std::endl;
		} else if (key == kWriteConfig) {
			video_control.WriteConfigToYAMLFile();
			std::cout << "Configuration YAML written." << std::endl;
		}

		video_control.GetTrackbarValue();
		capture.read(frame);
		cv::imshow("frame", frame);
	}
	
	cv::destroyAllWindows();
	
	return 0;
}

std::string GetCurrentTime() {
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	
	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
	ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
	return ss.str();
}
