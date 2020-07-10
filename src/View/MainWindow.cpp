#include "MainWindow.h"

#include <QFileDialog>
#include <QImage>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::BindLoadImage(const LoadImageTy &func) {
    LoadImage = func;
}
void MainWindow::BindSaveImage(const SaveImageTy &func) {
    SaveImage = func;
}

void MainWindow::OnLoadBtn() {
    auto filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
        tr("Image File (*.bmp, *.png, *.jpg)"));
    LoadImage(filename.toStdString(), img.data, img.width, img.height, img.n_channel);
    if (img.data == nullptr) {
        return;
    }

    auto fmt = QImage::Format_RGB888;
    if (img.n_channel == 1) {
        fmt = QImage::Format_Grayscale8;
    } else if (img.n_channel == 3) {
        fmt = QImage::Format_RGB888;
    } else if (img.n_channel == 4) {
        fmt = QImage::Format_RGBA8888;
    }
    QImage timg(img.data, img.width, img.height, img.width * img.n_channel * sizeof(uint8_t), fmt);
    auto pixmap = QPixmap::fromImage(timg);
    pixmap = pixmap.scaled(ui->image_lb->width(), ui->image_lb->height(), Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->image_lb->setPixmap(pixmap);
    ui->name_lb->setText(filename);

    SetGeoLabel();
}

void MainWindow::OnSaveBtn() {
    if (img.data == nullptr) {
        return;
    }

    auto filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".",
        tr("Image File (*.bmp, *.png, *.jpg)"));
    SaveImage(filename.toStdString(), img.data, img.width, img.height, img.n_channel);
}

void MainWindow::SetGeoLabel() {
    ui->geo_w_input->setText(QString::number(img.width));
    ui->geo_h_input->setText(QString::number(img.height));
}