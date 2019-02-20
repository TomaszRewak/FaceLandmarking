#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <exception>

namespace FaceLandmarking::App::UI
{
	class VideoCapture
	{
	private:
		cv::VideoCapture videoCapture;

		bool transform;
		int transformRotate;
		int transformWidth;
		int transformHeight;

		cv::Mat frameTransform;

	public:
		VideoCapture(
			std::string videoPath,
			bool transform,
			int transformRotate,
			int transformWidth,
			int transformHeight) :
			videoCapture(videoPath),
			transform(transform),
			transformRotate(transformRotate),
			transformWidth(transformWidth),
			transformHeight(transformHeight)
		{
			if (!videoCapture.isOpened())
				throw std::runtime_error("Video not found");
		}

		void loadFrame(cv::Mat& frame)
		{
			videoCapture >> frame;

			if (frame.empty()) {
				videoCapture.set(CV_CAP_PROP_POS_AVI_RATIO, 0);

				videoCapture >> frame;
			}

			if (transform)
			{
				cv::rotate(frame, frameTransform, transformRotate);
				frameTransform.copyTo(frame);
				cv::resize(frame, frameTransform, cv::Size(transformWidth, transformHeight));
				frameTransform.copyTo(frame);
			}
		}
	};
}