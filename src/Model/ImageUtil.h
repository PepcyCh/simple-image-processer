#pragma once

#include <iostream>

#include "Image.h"
#include "Mat.h"

using Kernel = Mat<double>;

class ImageUtil {
  public:
    ImageUtil() = delete;

    enum ImageType {
        IMG_TY_UNKNOWN,
        IMG_TY_JPG,
        IMG_TY_PNG,
        IMG_TY_BMP
    };
    static Image Load(const std::string &filename, ImageType ty);
    static void Save(const Image &img, const std::string &filename, ImageType ty);

    static Image RGB2YUV(const Image &img);
    static Image YUV2RGB(const Image &img);
    static Image RGB2Lab(const Image &img);
    static Image Lab2RGB(const Image &img);

    static Image GrayScale(const Image &img);
    static Image OtsuThreshold(const Image &img);

    enum AdaptiveThresholdMethod {
        MEAN,
        GAUSSIAN
    };
    static Image AdaptiveThreshold(const Image &img, int block_size, AdaptiveThresholdMethod method = MEAN,
        double minus = 0, double sx = 5, double sy = 5);

    static Image Erode(const Image &img, const Kernel &kernel, int anchor_x = -1, int anchor_y = -1,
        int iteration = 1);
    static Image Dilate(const Image &img, const Kernel &kernel, int anchor_x = -1, int anchor_y = -1,
        int iteration = 1);
    static Image Open(const Image &img, const Kernel &kernel, int anchor_x = -1, int anchor_y = -1,
        int iteration = 1);
    static Image Close(const Image &img, const Kernel &kernel, int anchor_x = -1, int anchor_y = -1,
        int iteration = 1);
        
    static Image Laplacian(const Image &img, double C);

    static Image Means(const Image &img, int block_size = 3, int iteration = 1);
    static Image Gaussian(const Image &img, int block_size = 3, double sigma = 1, int iteration = 1);
    static Image Median(const Image &img, int block_size = 3, int iteration = 1);
    static Image Bilateral(const Image &img, int block_size = 5, double sigma_s = 1, double sigma_r = 255,
        int iteration = 1);

    static Image Logarithm(const Image &img);

    static std::vector<double> GetHistogram(const Image &img);
    static std::vector<double> GetHistogram(const Image &img, int cid);
    static Image HistogramEqualize(const Image &img);
    static Image HistogramFit(const Image &img, const std::vector<double> &hist);
    static Image HistogramFit(const Image &img, const std::vector<double> &hist, int cid);

    static Image Curve(const Image &img, const std::vector<std::pair<int, int>> &points);
    static Image Curve(const Image &img, const std::vector<std::pair<int, int>> &points, int cid);
    
    static Image Rotate(const Image &img, double angle);
    static Image Scale(const Image &img, double sx, double sy);
    static Image ShearX(const Image &img, double dx);
    static Image ShearY(const Image &img, double dy);
    static Image MirrorX(const Image &img);
    static Image MirrorY(const Image &img);

  private:
    static Kernel GetGaussian1D(int length, double sigma);
    static Kernel GetGaussian2D(int width, int height, double sigma_x, double sigma_y);

    static std::pair<int, int> Adjust(Image &img);
};