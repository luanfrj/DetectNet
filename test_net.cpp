/*
 * This code was made to forward a image and get the car predictions using the DetectNet
 * it receive as input one image and save result in a kitti's format txt file.
 * Author: Luan
 */


#include "detect_net.hpp"

#include <stdio.h>

int main(int argc, char **argv)
{
	std::string model_file = "deploy.prototxt";
	std::string trained_file = "snapshot_iter_21600.caffemodel";

	if (argc < 2)
	{
		printf("Usage %s <image filename>\n", argv[0]);
		return -1;
	}
	std::string file = argv[1];
	int gpu = 1;
	int device_id = 0;

	// loads the detect net
	DetectNet detectNet(model_file, trained_file, gpu, device_id);

	cv::Mat img = cv::imread(file, -1);

	// forward the image through the network
	std::vector<float> result = detectNet.Predict(img);

	// fix the scale of image
	float correction_x = img.cols / 1250.0;
	float correction_y = img.rows / 380.0;

	char output_file_name[25];
	sprintf(output_file_name, "%s.txt", argv[1]);

	FILE *output_file = fopen(output_file_name, "w");

	for (int i = 0; i < 10; i++)
	{
		// top left
		float xt = result[5*i] * correction_x;
		float yt = result[5*i + 1] * correction_y;

		// botton right
		float xb = result[5*i + 2] * correction_x;
		float yb = result[5*i + 3] * correction_y;

		float confidence = result[5*i + 4];
		if (confidence > 0.0)
		{
			fprintf(output_file, "Car 0.00 0 0.00 %.2f %.2f %.2f %.2f 0.00 0.00 0.00 0.00 0.00 0.00 0 %.2f\n", xt, yt, xb, yb, confidence);
			//cv::rectangle(img, cv::Point(xt,yt), cv::Point(xb,yb), cv::Scalar(0,255,0), 2);
		}
	}

	/*
	if (img.empty())
	{
		printf("image empty\n");
	}
	else
	{
		cv::imshow("Image", img);
		cv::waitKey(0);
	}
	*/
	return 0;
}
