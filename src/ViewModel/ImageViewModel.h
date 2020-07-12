#pragma once

#include <memory>
#include <functional>

#include "ImageModel.h"

class ImageViewModel {
  public:
    void BindModel(const std::shared_ptr<ImageModel> &_image_model);
    void ReleaseModel();

    using LoadImageTy = std::function<void(const std::string &, Image &)>;
    [[nodiscard]] LoadImageTy LoadImageFunc() const;
    using SaveImageTy = std::function<void(const std::string &)>;
    [[nodiscard]] SaveImageTy SaveImageFunc() const;
    using UndoImageTy = std::function<void(Image &)>;
    [[nodiscard]] UndoImageTy UndoImageFunc() const;
    using RedoImageTy = std::function<void(Image &)>;
    [[nodiscard]] RedoImageTy RedoImageFunc() const;
    using GrayScaleTy = std::function<void(Image &)>;
    [[nodiscard]] GrayScaleTy GrayScaleFunc() const;

  private:
    std::shared_ptr<ImageModel> image_model;
};