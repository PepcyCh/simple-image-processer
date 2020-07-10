#include "ImageViewModel.h"

static Image::Type GetImageType(const std::string &filename) {
    auto pos = filename.rfind('.');
    auto suffix = filename.substr(pos + 1, filename.size());
    if (suffix == "jpg") {
        return Image::Type::JPG;
    } else if (suffix == "png") {
        return Image::Type::PNG;
    } else if (suffix == "bmp") {
        return Image::Type::BMP;
    } else {
        return Image::Type::UNKNOWN;
    }
}

void ImageViewModel::BindModel(const std::shared_ptr<ImageModel> &_image_model) {
    image_model = _image_model;
}

void ImageViewModel::ReleaseModel() {
    image_model.reset();
}

ImageViewModel::LoadImageTy ImageViewModel::LoadImageFunc() const {
    return [this](const std::string &filename, const uint8_t *&data, int &w, int &h, int &nn) {
        auto fmt = GetImageType(filename);
        Image img = Image::Load(filename, fmt);
        if (img.Empty()) {
            data = nullptr;
            return;
        }
        data = img.GetData();
        w = img.GetWidth();
        h = img.GetHeight();
        nn = 4;
        image_model->Reset();
        image_model->PushImage(img);
    };
}

ImageViewModel::SaveImageTy ImageViewModel::SaveImageFunc() const {
    return [this](const std::string &_filename) {
        auto filename = _filename;
        auto fmt = GetImageType(filename);
        if (fmt == Image::Type::UNKNOWN) {
            fmt = Image::Type::JPG;
            filename += ".jpg";
        }
        auto img = image_model->GetCurrent();
        img.Save(filename, fmt);
    };
}