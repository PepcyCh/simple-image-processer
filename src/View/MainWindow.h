#pragma once

#include <iostream>
#include <cassert>
#include <cstdint>
#include <string>
#include <functional>

#include <QWidget>
#include "ui_MainWindow.h"

class MainWindow : public QWidget {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    using LoadImageTy = std::function<void(const std::string &, const uint8_t *&, int &, int &, int &)>;
    void BindLoadImage(const LoadImageTy &func);
    using SaveImageTy = std::function<void(const std::string &)>;
    void BindSaveImage(const SaveImageTy &func);

  private:
    Ui::MainWindow *ui;

    bool has_image = false;

    LoadImageTy LoadImage;
    SaveImageTy SaveImage;

    void SetGeoLabel(int w, int h);

  private slots:
    void OnLoadBtn();
    void OnSaveBtn();
};