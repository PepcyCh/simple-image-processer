#pragma once

#include <memory>
#include <functional>
#include <array>

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
    using ThresholdTy = std::function<void(Image &)>;
    [[nodiscard]] ThresholdTy ThresholdFunc() const;
    using AdapThresTy = std::function<void(Image &, int, int)>;
    [[nodiscard]] AdapThresTy AdapThresFunc() const;

    using EqualizationTy = std::function<void(Image &)>;
    [[nodiscard]] EqualizationTy EqualizationFunc() const;
    using SharpenTy = std::function<void(Image &, double)>;
    [[nodiscard]] SharpenTy SharpenFunc() const;
    using HistogramTy = std::function<void(std::array<Image, 4> &)>;
    [[nodiscard]] HistogramTy HistogramFunc() const;

    using ScaleTy = std::function<void(Image &, double, double)> ;
    [[nodiscard]] ScaleTy ScaleFunc() const;
    using RotateTy = std::function<void(Image &, double)> ;
    [[nodiscard]] RotateTy RotateFunc() const;
    using ShearXTy = std::function<void(Image &, double)> ;
    [[nodiscard]] ShearXTy ShearXFunc() const;
    using ShearYTy = std::function<void(Image &, double)> ;
    [[nodiscard]] ShearYTy ShearYFunc() const;

  private:
    std::shared_ptr<ImageModel> image_model;
};