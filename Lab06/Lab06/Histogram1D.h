class Histogram1D {

private:
	int histSize[1];          // number of bins in histogram 
	float hranges[2];         // range of values 
	const float* ranges[1];   // pointer to the value ranges 
	int channels[1];          // channel number to be examined 

public:
	Histogram1D() {

		// Prepare default arguments for 1D histogram 
		histSize[0] = 256;        // 256 bins 
		hranges[0] = 0.0;         // from 0 (inclusive) 
		hranges[1] = 256.0;       // to 256 (exclusive) 
		ranges[0] = hranges;
		channels[0] = 0;          // we look at channel 0 
	}
	
	cv::Mat getHistogram(const cv::Mat &image) {

		cv::Mat hist;
		// Compute 1D histogram with calcHist 
		cv::calcHist(&image, 1, // histogram of 1 image only 
			channels,  // the channel used 
			cv::Mat(), // no mask is used 
			hist,      // the resulting histogram 
			1,         // it is a 1D histogram 
			histSize,  // number of bins 
			ranges     // pixel value range 
		);

		return hist;
	}

	// Computes the 1D histogram and returns an image of it. 
	cv::Mat getHistogramImage(const cv::Mat &image, int zoom = 1) {

		// Compute histogram first 
		cv::Mat hist = getHistogram(image);
		// Creates image 
		return getImageOfHistogram(hist, zoom);
	}

	// Create an image representing a histogram (static method) 
	static cv::Mat getImageOfHistogram(const cv::Mat &hist, int zoom) {
		// Get min and max bin values 
		double maxVal = 0;
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

		// get histogram size 
		int histSize = hist.rows;

		// Square image on which to display histogram 
		cv::Mat histImg(histSize*zoom, histSize*zoom,
			CV_8U, cv::Scalar(255));

		// set highest point at 90% of nbins (i.e. image height) 
		int hpt = static_cast<int>(0.9*histSize);

		// Draw vertical line for each bin  
		for (int h = 0; h < histSize; h++) {

			float binVal = hist.at<float>(h);
			if (binVal>0) {
				int intensity = static_cast<int>(binVal*hpt / maxVal);
				cv::line(histImg, cv::Point(h*zoom, histSize*zoom),
					cv::Point(h*zoom, (histSize - intensity)*zoom),
					cv::Scalar(0), zoom);
			}
		}

		return histImg;
	}
};
