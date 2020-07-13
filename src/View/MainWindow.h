#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <string>
#include <functional>

#include <QWidget>
#include "ui_MainWindow.h"

#include "AdapThresDialog.h"

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
    void BindEqualization(const ThresholdTy &func);

    using ScaleTy = std::function<void(Image &, double, double)>;
    void BindScale(const ScaleTy &func);

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

    ScaleTy Scale;

    std::unique_ptr<AdapThresDialog> adap_thres_dialog;

    struct {
        int block_size, bias;
    } params;

    void InitDialogs();

    void SetGeoLabel(int w, int h);
    void ShowImage();

    void SetAdapThresParams(int block_size, int bias);

  private slots:
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
};