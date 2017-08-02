/*
 * Author: Luan
 */

#include <caffe/caffe.hpp>
#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV

class DetectNet
{
public:
	DetectNet(const std::string &model_file, const std::string& trained_file, int GPU, int device_id);
	
	std::vector<float> Predict(const cv::Mat& img);
	
	void WrapInputLayer(std::vector<cv::Mat>* input_channels);

	void Preprocess(const cv::Mat& img, std::vector<cv::Mat>* input_channels);
private:
	boost::shared_ptr<caffe::Net> net_;
	cv::Size input_geometry_;
	int num_channels_;
};
