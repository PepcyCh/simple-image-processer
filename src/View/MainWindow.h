#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>
#include <functional>

#include <QWidget>
#include <QShortcut>
#include "ui_MainWindow.h"

#include "AdapThresDialog.h"
#include "HistogramDialog.h"
#include "BlurDialog.h"

#include "Image.h"

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    using LoadImageTy = std::function<void(const std::string &, Image &)>;
    void BindLoadImage(const LoadImageTy &func);
    using SaveImageTy = std::function<void(const std::string &)>;
    void BindSaveImage(const SaveImageTy &func);
    using UndoImageTy = std::function<void(Image &)>;
    void BindUndoImage(const UndoImageTy &func);
    using RedoImageTy = std::function<void(Image &)>;
    void BindRedoImage(const RedoImageTy &func);

    using GrayScaleTy = std::function<void(Image &)>;
    void BindGrayScale(const GrayScaleTy &func);
    using ThresholdTy = std::function<void(Image &)>;
    void BindThreshold(const ThresholdTy &func);
    using AdapThresTy = std::function<void(Image &, int, int)>;
    void BindAdapThres(const AdapThresTy &func);

    using EqualizationTy = std::function<void(Image &)>;
    void BindEqualization(const EqualizationTy &func);
    using SharpenTy = std::function<void(Image &, double C)>;
    void BindSharpen(const SharpenTy &func);
    using HistogramTy = std::function<void(std::array<Image, 4> &)>;
    void BindHistogram(const HistogramTy &func);

    using ScaleTy = std::function<void(Image &, double, double)>;
    void BindScale(const ScaleTy &func);
    using RotateTy = std::function<void(Image &, double)>;
    void BindRotate(const RotateTy &func);

    using ShearXTy = std::function<void(Image &, double)>;
    void BindShearX(const ShearXTy &func);
    using ShearYTy = std::function<void(Image &, double)>;
    void BindShearY(const ShearYTy &func);

    using MedianTy = std::function<void(Image &, int, int)>;
    void BindMedian(const MedianTy &func);
    using MeansTy = std::function<void(Image &, int, int)>;
    void BindMeans(const MeansTy &func);
    using GaussTy = std::function<void(Image &, int, double, int)>;
    void BindGauss(const GaussTy &func);
    using BilateralTy = std::function<void(Image &, int, double, double, int)>;
    void BindBilateral(const BilateralTy &func);


  private:
    Ui::MainWindow *ui;

    bool has_image = false;
    Image shown_image;
    QString filename;

    LoadImageTy LoadImage;
    SaveImageTy SaveImage;
    UndoImageTy UndoImage;
    RedoImageTy RedoImage;

    GrayScaleTy GrayScale;
    ThresholdTy Threshold;
    AdapThresTy AdapThres;

    EqualizationTy Equalization;
    SharpenTy Sharpen ;
    HistogramTy Histogram ;

    ScaleTy Scale;
    RotateTy Rotate ;

    ShearXTy ShearX ;
    ShearYTy ShearY ;

    MedianTy Median ;
    MeansTy Means ;
    GaussTy Gauss ;
    BilateralTy Bilateral ;


    std::unique_ptr<AdapThresDialog> adap_thres_dialog;
    std::unique_ptr<HistogramDialog> histogram_dialog;
    std::unique_ptr<BlurDialog> blur_dialog;

    struct {
        int block_size, bias;
    } params;
    struct {
            int opt, block_size, tim ;
            double sigma[2] ;
    } BlurParams ;

    void InitDialogs();
    void InitShortcuts();
    void InitValidators();

    void SetGeoLabel(int w, int h);
    void ShowImage();

  private slots:
    void SetAdapThresParams(int block_size, int bias);
    void SetBlurParams(int opt, int block_size, int tim, double sigma_0, double sigma_1) ;

    void OnLoadBtn();
    void OnSaveBtn();
    void OnUndoBtn();
    void OnRedoBtn();

    void OnGrayScaleBtn();
    void OnThresholdBtn();
    void OnAdapThresBtn();

    void OnGeoWBtn() ;
    void OnGeoHBtn() ;
    void OnRotBtn() ;
    void OnShrXBtn() ;
    void OnShrYBtn() ;

    void OnEqualizationBtn();
    void OnSharpenBtn() ;
    void OnHistBtn() ;
    void OnBlurBtn() ;
};