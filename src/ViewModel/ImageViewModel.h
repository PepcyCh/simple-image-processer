#pragma once

#include <memory>
#include <functional>

#include "ImageModel.h"

class ImageViewModel {
  public:
    void BindModel(const std::shared_ptr<ImageModel> &_image_model);
    void ReleaseModel();

    using LoadImageTy = std::function<void(const std::string &, const uint8_t *&, int &, int &, int &)>;
    LoadImageTy LoadImageFunc() const;
    using SaveImageTy = std::function<void(const std::string &)>;
    SaveImageTy SaveImageFunc() const;

  private:
    std::shared_ptr<ImageModel> image_model;
};