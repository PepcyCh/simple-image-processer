#include <iostream>

#include "Image.h"
#include "ImageUtil.h"
#include "MathUtil.h"

void TestImage(const std::string &filename, const std::string &suf, Image::Type ty) {
    Image img = Image::Load(filename + suf, ty);
    if (img.Empty()) {
        std::cout << "'" << filename << suf << "' is an empty image" << std::endl;
        return;
    }
    std::cout << "load image '" << filename << suf << "' succefully" << std::endl;
    img.Save(filename + "_copy" + suf, ty);

    // Gray Scale
    Image gs = ImageUtil::GrayScale(img);
    gs.Save(filename + "_gray" + suf, ty);
    ImageUtil::OtsuThreshold(gs).Save(filename + "_otsu" + suf, ty);
    ImageUtil::AdaptiveThreshold(gs, 30, ImageUtil::MEAN, 10).Save(filename + "_adptthres" + suf, ty);

    // Enhance
    ImageUtil::Laplacian(img, 5.0).Save(filename + "_lap" + suf, ty);
    ImageUtil::Means(img, 5).Save(filename + "_means" + suf, ty);
    ImageUtil::Median(img, 5).Save(filename + "_median" + suf, ty);
    ImageUtil::Gaussian(img, 5).Save(filename + "_gauss" + suf, ty);
    ImageUtil::Bilateral(img, 5).Save(filename + "_bi" + suf, ty);
    ImageUtil::HistogramEqualize(img).Save(filename + "_equa" + suf, ty);

    // Geometry
    ImageUtil::Rotate(img, MathUtil::Radians(30)).Save(filename + "_rot" + suf, ty);
    ImageUtil::Scale(img, 0.4, 0.5).Save(filename + "_scl" + suf, ty);
    ImageUtil::ShearX(img, 50).Save(filename + "_shrx" + suf, ty);
    ImageUtil::ShearY(img, 50).Save(filename + "_shry" + suf, ty);
}

int main() {
    TestImage("./img/tree", ".jpg", Image::Type::JPG);
    TestImage("./img/text", ".jpg", Image::Type::JPG);

    return 0;
}