//
// Created by Filene on 2020/7/12.
//

#ifndef IMAGE_PROCESSER_APPPROCESS_H
#define IMAGE_PROCESSER_APPPROCESS_H

#include "ImageModel.h"
#include "MainWindow.h"
#include "ImageViewModel.h"
class APP{
public:
    APP();
    void Run_APP();

private:
    void BindModel(const std::shared_ptr<ImageModel> &_image_model);
    void ReleaseModel();

    void BindViewModel(const std::shared_ptr<ImageViewModel> &_image_view_model);
    void ReleaseViewModel();

    void BindMainWindow(const std::shared_ptr<MainWindow> &_mainwindow);
    void ReleaseMainWindow();

private:
    std::shared_ptr<ImageModel> image_model;
    std::shared_ptr<ImageViewModel> image_view_model;
    std::shared_ptr<MainWindow> mainwindow;
};
#endif //IMAGE_PROCESSER_APPPROCESS_H
