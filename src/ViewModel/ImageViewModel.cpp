#include "ImageViewModel.h"

#include "ImageUtil.h"

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
