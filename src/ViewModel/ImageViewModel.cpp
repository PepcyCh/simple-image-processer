#include "ImageViewModel.h"

#include "ImageUtil.h"
#include "MathUtil.h"

static ImageUtil::ImageType GetImageType(const std::string &filename) {
    auto pos = filename.rfind('.');
    auto suffix = filename.substr(pos + 1, filename.size());
    if (suffix == "jpg" || suffix == "jpeg") {
        return ImageUtil::IMG_TY_JPG;
    } else if (suffix == "png") {
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
    return [this](const std::string &filename, Image *&img) {
        auto fmt = GetImageType(filename);
        Image _img = ImageUtil::Load(filename, fmt);
        if (_img.Empty()) {
            img = nullptr;
            return;
        }
        image_model->Reset();
        img = image_model->PushImage(std::move(_img));
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
        const Image &img = *image_model->GetCurrent();
        ImageUtil::Save(img, filename, fmt);
    };
}

ImageViewModel::UndoImageTy ImageViewModel::UndoImageFunc() const {
    return [this](Image *&img) {
        if (image_model->CanUndo()) {
            img = image_model->Undo();
        }
    };
}

ImageViewModel::RedoImageTy ImageViewModel::RedoImageFunc() const {
    return [this](Image *&img) {
        if (image_model->CanRedo()) {
            img = image_model->Redo();
        }
    };
}

ImageViewModel::GrayScaleTy ImageViewModel::GrayScaleFunc() const {
    return [this](Image *&img) {
        Image _img = ImageUtil::GrayScale(*img);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::ThresholdTy ImageViewModel::ThresholdFunc() const {
    return [this](Image *&img) {
        Image _img = ImageUtil::OtsuThreshold(*img);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::AdapThresTy ImageViewModel::AdapThresFunc() const {
    return [this](Image *&img, int block_size, int bias) {
        Image _img = ImageUtil::AdaptiveThreshold(*img, block_size, ImageUtil::MEAN, bias);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::EqualizationTy ImageViewModel::EqualizationFunc() const {
    return [this](Image *&img) {
        Image _img = ImageUtil::HistogramEqualize(*img);
        img = image_model->PushImage(std::move(_img));
    };
}


ImageViewModel::SharpenTy ImageViewModel::SharpenFunc() const {
    return [this](Image *&img, double C) {
        Image _img = ImageUtil::Laplacian(*img, C);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::HistogramTy ImageViewModel::HistogramFunc() const {
    return [this](std::array<Image, 4> &imgs) {
        imgs = ImageUtil::GetHistogramImage(*image_model->GetCurrent());
    };
}

ImageViewModel::MedianTy ImageViewModel::MedianFunc() const {
    return [this](Image *&img, int block_size, int iteration) {
        Image _img = ImageUtil::Median(*img, block_size, iteration);
        img = image_model->PushImage(std::move(_img));
    };
}
ImageViewModel::MeansTy ImageViewModel::MeansFunc() const {
    return [this](Image *&img, int block_size, int iteration) {
        Image _img = ImageUtil::Means(*img, block_size, iteration);
        img = image_model->PushImage(std::move(_img));
    };
}
ImageViewModel::GaussTy ImageViewModel::GaussFunc() const {
    return [this](Image *&img, int block_size, double sigma, int iteration) {
        Image _img = ImageUtil::Gaussian(*img, block_size, sigma, iteration);
        img = image_model->PushImage(std::move(_img));
    };
}
ImageViewModel::BilateralTy ImageViewModel::BilateralFunc() const {
    return [this](Image *&img, int block_size, double sigma_s, double sigma_r, int iteration) {
        Image _img = ImageUtil::Bilateral(*img, block_size, sigma_s, sigma_r, iteration);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::ScaleTy ImageViewModel::ScaleFunc() const {
    return [this](Image *&img, double sx, double sy) {
        Image _img = ImageUtil::Scale(*img, sx, sy);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::RotateTy ImageViewModel::RotateFunc() const {
    return [this](Image *&img, double ang) {
        Image _img = ImageUtil::Rotate(*img, MathUtil::Radians(ang));
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::ShearXTy ImageViewModel::ShearXFunc() const {
    return [this](Image *&img, double dx) {
        Image _img = ImageUtil::ShearX(*img, dx);
        img = image_model->PushImage(std::move(_img));
    };
}

ImageViewModel::ShearYTy ImageViewModel::ShearYFunc() const {
    return [this](Image *&img, double dy) {
        Image _img = ImageUtil::ShearY(*img, dy);
        img = image_model->PushImage(std::move(_img));
    };
}