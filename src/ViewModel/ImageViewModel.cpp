#include "ImageViewModel.h"

#include "ImageUtil.h"
#include "MathUtil.h"

static ImageUtil::ImageType GetImageType(const std::string &filename) {
    auto pos = filename.rfind('.');
    auto suffix = filename.substr(pos + 1, filename.size());
    if (suffix == "jpg" || suffix == "jpeg") {
        return ImageUtil::IMG_TY_JPG;
    } else if (suffix == "png") { // Don't identify png? That's weird.
        return ImageUtil::IMG_TY_PNG;
    } else if (suffix == "bmp") {
        return ImageUtil::IMG_TY_BMP;
    } else {
        return ImageUtil::IMG_TY_UNKNOWN;
    }
}

void ImageViewModel::BindModel(const std::shared_ptr<ImageModel> &_image_model) {
    image_model = _image_model;
}

void ImageViewModel::ReleaseModel() {
    image_model.reset();
}

ImageViewModel::LoadImageTy ImageViewModel::LoadImageFunc() const {
    return [this](const std::string &filename, Image &img) {
        auto fmt = GetImageType(filename);
        img = ImageUtil::Load(filename, fmt);
        if (img.Empty()) {
            return;
        }
        image_model->Reset();
        image_model->PushImage(img);
    };
}

ImageViewModel::SaveImageTy ImageViewModel::SaveImageFunc() const {
    return [this](const std::string &_filename) {
        auto filename = _filename;
        auto fmt = GetImageType(filename);
        if (fmt == ImageUtil::IMG_TY_UNKNOWN) {
            fmt = ImageUtil::IMG_TY_JPG;
            filename += ".jpg";
        }
        auto img = image_model->GetCurrent();
        ImageUtil::Save(img, filename, fmt);
    };
}

ImageViewModel::UndoImageTy ImageViewModel::UndoImageFunc() const {
    return [this](Image &img) {
        if (image_model->CanUndo()) {
            img = image_model->Undo(); // Warning: Use Default Constructor.
        }
    };
}

ImageViewModel::RedoImageTy ImageViewModel::RedoImageFunc() const {
    return [this](Image &img) {
        if (image_model->CanRedo()) {
            img = image_model->Redo(); // Warning: Use Default Constructor.
        }
    };
}

ImageViewModel::GrayScaleTy ImageViewModel::GrayScaleFunc() const {
    return [this](Image &img) {
        img = ImageUtil::GrayScale(img);
        image_model->PushImage(img);
    };
}

ImageViewModel::ThresholdTy ImageViewModel::ThresholdFunc() const {
    return [this](Image &img) {
        img = ImageUtil::OtsuThreshold(img);
        image_model->PushImage(img);
    };
}

ImageViewModel::AdapThresTy ImageViewModel::AdapThresFunc() const {
    return [this](Image &img, int block_size, int bias) {
        img = ImageUtil::AdaptiveThreshold(img, block_size, ImageUtil::MEAN, bias);
        image_model->PushImage(img);
    };
}

ImageViewModel::EqualizationTy ImageViewModel::EqualizationFunc() const {
    return [this](Image &img) {
        img = ImageUtil::HistogramEqualize(img);
        image_model->PushImage(img);
    };
}


ImageViewModel::SharpenTy ImageViewModel::SharpenFunc() const {
    return [this](Image &img, double C) {
        img = ImageUtil::Laplacian(img, C);
        image_model->PushImage(img);
    };
}

ImageViewModel::HistogramTy ImageViewModel::HistogramFunc() const {
    return [this](std::array<Image, 4> &imgs) {
        imgs = ImageUtil::GetHistogramImage(image_model->GetCurrent());
    };
}

ImageViewModel::MedianTy ImageViewModel::MedianFunc() const {
    return [this](Image &img, int block_size, int iteration) {
        img = ImageUtil::Median(img, block_size, iteration);
        image_model->PushImage(img);
    };
}
ImageViewModel::MeansTy ImageViewModel::MeansFunc() const {
    return [this](Image &img, int block_size, int iteration) {
        img = ImageUtil::Means(img, block_size, iteration);
        image_model->PushImage(img);
    };
}
ImageViewModel::GaussTy ImageViewModel::GaussFunc() const {
    return [this](Image &img, int block_size, double sigma, int iteration) {
        img = ImageUtil::Gaussian(img, block_size, sigma, iteration);
        image_model->PushImage(img);
    };
}
ImageViewModel::BilateralTy ImageViewModel::BilateralFunc() const {
    return [this](Image &img, int block_size, double sigma_s, double sigma_r, int iteration) {
        img = ImageUtil::Bilateral(img, block_size, sigma_s, sigma_r, iteration);
        image_model->PushImage(img);
    };
}

ImageViewModel::ScaleTy ImageViewModel::ScaleFunc() const {
    return [this](Image &img, double sx, double sy) {
        img = ImageUtil::Scale(img, sx, sy);
        image_model->PushImage(img);
    };
}

ImageViewModel::RotateTy ImageViewModel::RotateFunc() const {
    return [this](Image &img, double ang) {
        img = ImageUtil::Rotate(img, MathUtil::Radians(ang));
        image_model->PushImage(img);
    };
}

ImageViewModel::ShearXTy ImageViewModel::ShearXFunc() const {
    return [this](Image &img, double dx) {
        img = ImageUtil::ShearX(img, dx);
        image_model->PushImage(img);
    };
}

ImageViewModel::ShearYTy ImageViewModel::ShearYFunc() const {
    return [this](Image &img, double dy) {
        img = ImageUtil::ShearY(img, dy);
        image_model->PushImage(img);
    };
}