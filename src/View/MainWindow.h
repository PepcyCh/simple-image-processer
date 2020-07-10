#pragma once

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
    using SaveImageTy = std::function<void(const std::string &, const uint8_t *, int, int, int)>;
    void BindSaveImage(const SaveImageTy &func);

  private:
    Ui::MainWindow *ui;

    struct Image {
        const uint8_t *data;
        int width;
        int height;
        int n_channel;
    } img;

    LoadImageTy LoadImage;
    SaveImageTy SaveImage;

    void SetGeoLabel();

  private slots:
    void OnLoadBtn();
    void OnSaveBtn();
};