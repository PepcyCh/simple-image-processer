#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>
#include <string>
#include <functional>

#include <QWidget>
#include "ui_MainWindow.h"

#include "Image.h"

// class Parameter{
// public:
//     Parameter();
// };

// class Command{
// public:
//     Command();
//     void BindParameters(std::shared_ptr<Parameter> _parameters){
//         parameters = _parameters;
//     }
//     virtual void run() = 0;
// protected:
//     std::shared_ptr<Parameter> parameters;
// };

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    using LoadImageTy = std::function<void(const std::string &, Image &)>;
    void BindLoadImage(const LoadImageTy &func);
    using SaveImageTy = std::function<void(const std::string &)>;
    void BindSaveImage(const SaveImageTy &func);

  private:
    Ui::MainWindow *ui;

    bool has_image = false;
    Image shown_image;

    LoadImageTy LoadImage;
    SaveImageTy SaveImage;

    void SetGeoLabel(int w, int h);

  private slots:
    void OnLoadBtn();
    void OnSaveBtn();
};