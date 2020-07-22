#pragma once

#include <array>
#include <vector>

#include "Image.h"
#include "Mat.h"

using Kernel = Mat<double>;

/*注：由于在ImageUtil库中，所有函数都采取了函数内部新建一个Image类型的变量的做法：
 * 比如：
 * Image func(const Image &img) {
 *     Image res;
 *     return res;
 * }
 * 在返回的时候 由于返回的是local function的变量，无法使用const Image&进行返回；
 * 好消息是，编译器对于这种类型的返回值会强制加以右值，对于所有调用：
 * Image x = func(x);
 * 这类赋值语句，采取的行为等价于 x = std::move(func(x))，它会进行自发的移动构造，因此没有对图形库代码进行修改。
*/
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
    static std::array<Image, 4> GetHistogramImage(const Image &img);
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