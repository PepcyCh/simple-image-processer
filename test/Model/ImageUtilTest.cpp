#include <iostream>

#include "Image.h"
#include "ImageUtil.h"
#include "MathUtil.h"

void TestImage(const std::string &filename, const std::string &suf, ImageUtil::ImageType ty) {
    Image img = ImageUtil::Load(filename + suf, ty);
    if (img.Empty()) {
        std::cout << "'" << filename << suf << "' is an empty image" << std::endl;
        return;
    }
    std::cout << "load image '" << filename << suf << "' succefully" << std::endl;
    ImageUtil::Save(img, filename + "_copy" + suf, ty);

    // Gray Scale
    Image gs = ImageUtil::GrayScale(img);
    ImageUtil::Save(gs, filename + "_gray" + suf, ty);
    ImageUtil::Save(ImageUtil::OtsuThreshold(gs), filename + "_otsu" + suf, ty);
    ImageUtil::Save(ImageUtil::AdaptiveThreshold(gs, 30, ImageUtil::MEAN, 10), filename + "_adptthres" + suf, ty);

    // Enhance
    ImageUtil::Save(ImageUtil::Laplacian(img, 5.0), filename + "_lap" + suf, ty);
    ImageUtil::Save(ImageUtil::Means(img, 5), filename + "_means" + suf, ty);
    ImageUtil::Save(ImageUtil::Median(img, 5), filename + "_median" + suf, ty);
    ImageUtil::Save(ImageUtil::Gaussian(img, 5), filename + "_gauss" + suf, ty);
    ImageUtil::Save(ImageUtil::Bilateral(img, 5), filename + "_bi" + suf, ty);
    ImageUtil::Save(ImageUtil::HistogramEqualize(img), filename + "_equa" + suf, ty);

    // Geometry
    ImageUtil::Save(ImageUtil::Rotate(img, MathUtil::Radians(30)), filename + "_rot" + suf, ty);
    ImageUtil::Save(ImageUtil::Scale(img, 0.4, 0.5), filename + "_scl" + suf, ty);
    ImageUtil::Save(ImageUtil::ShearX(img, 50), filename + "_shrx" + suf, ty);
    ImageUtil::Save(ImageUtil::ShearY(img, 50), filename + "_shry" + suf, ty);
    
    // histogram
    auto hist_imgs = ImageUtil::GetHistogramImage(img);
    ImageUtil::Save(hist_imgs[0], filename + "_hist.png", ImageUtil::IMG_TY_PNG);
    ImageUtil::Save(hist_imgs[1], filename + "_hist_r.png", ImageUtil::IMG_TY_PNG);
    ImageUtil::Save(hist_imgs[2], filename + "_hist_g.png", ImageUtil::IMG_TY_PNG);
    ImageUtil::Save(hist_imgs[3], filename + "_hist_b.png", ImageUtil::IMG_TY_PNG);
}

int main() {
    TestImage("./img/tree", ".jpg", ImageUtil::IMG_TY_JPG);
    TestImage("./img/text", ".jpg", ImageUtil::IMG_TY_JPG);

    return 0;
}