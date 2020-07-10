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
    const uint8_t *data;
    int nx, ny, nn;
    LoadImage(filename.toStdString(), data, nx, ny, nn);
    if (data == nullptr) {
        return;
    }

    auto fmt = QImage::Format_RGB888;
    if (nn == 1) {
        fmt = QImage::Format_Grayscale8;
    } else if (nn == 3) {
        fmt = QImage::Format_RGB888;
    } else if (nn == 4) {
        fmt = QImage::Format_RGBA8888;
    }
    QImage img(data, nx, ny, nx * nn * sizeof(uint8_t), fmt);
    auto pixmap = QPixmap::fromImage(img);
    pixmap = pixmap.scaled(ui->image_lb->width(), ui->image_lb->height(), Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->image_lb->setPixmap(pixmap);
    ui->name_lb->setText(filename);
}

void MainWindow::OnSaveBtn() {
    auto filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
        tr("Image File (*.bmp, *.png, *.jpg)"));
    QImage img = ui->image_lb->pixmap()->toImage();
    const uint8_t *data = img.constBits();
    int width = img.width();
    int height = img.height();
    int nn = 3;
    auto fmt = img.format();
    if (fmt == QImage::Format_Grayscale8) {
        nn = 1;
    } else if (fmt == QImage::Format_RGB888) {
        nn = 3;
    } else if (fmt == QImage::Format_RGBA8888) {
        nn = 4;
    }
    SaveImage(filename.toStdString(), data, width, height, nn);
}