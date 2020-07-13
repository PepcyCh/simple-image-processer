#include "appprocess.h"

void APP::BindModel(const std::shared_ptr<ImageModel> &_image_model) {
    image_model = _image_model;
}

void APP::ReleaseModel() {
    image_model.reset();
}

void APP::BindViewModel(const std::shared_ptr<ImageViewModel> &_image_view_model) {
    image_view_model = _image_view_model;
}

void APP::ReleaseViewModel() {
    image_view_model.reset();
}

void APP::BindMainWindow(const std::shared_ptr<MainWindow> &_mainwindow) {
    mainwindow = _mainwindow;
}

void APP::ReleaseMainWindow() {
    mainwindow.reset();
}

APP::APP(): mainwindow(new MainWindow), image_view_model(new ImageViewModel), image_model(new ImageModel) {
    // mainwindow: view.
    image_view_model->BindModel(image_model);
    // Bind Model.

    //Bind Commands.
    mainwindow->BindLoadImage(image_view_model->LoadImageFunc());
    mainwindow->BindSaveImage(image_view_model->SaveImageFunc());
    mainwindow->BindRedoImage(image_view_model->RedoImageFunc());
    mainwindow->BindUndoImage(image_view_model->UndoImageFunc());

    mainwindow->BindGrayScale(image_view_model->GrayScaleFunc());
    mainwindow->BindThreshold(image_view_model->ThresholdFunc());
    mainwindow->BindAdapThres(image_view_model->AdapThresFunc());

    mainwindow->BindEqualization(image_view_model->EqualizationFunc());
}

void APP::Run_APP() {
    mainwindow->show();
}
