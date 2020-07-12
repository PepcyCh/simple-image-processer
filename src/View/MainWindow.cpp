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
    std::string s = std::string(filename.toLocal8Bit()); // fix a bug here. (DON'T use toStdString)
    LoadImage(s, shown_image);
    if (shown_image.Empty()) {
        return;
    }

    int nx = shown_image.GetWidth();
    int ny = shown_image.GetHeight();
    int nn = shown_image.GetChannelCnt();
    const uint8_t *data = shown_image.GetData();

    auto fmt = QImage::Format_RGB888;
    if (nn == 1) {
        fmt = QImage::Format_Grayscale8;
    } else if (nn == 3) {
        fmt = QImage::Format_RGB888;
    } else if (nn == 4) {
        fmt = QImage::Format_RGBA8888;
    }
    QImage qimg(data, nx, ny, nx * nn * int(sizeof(uint8_t)), fmt);
    auto pixmap = QPixmap::fromImage(qimg);
    pixmap = pixmap.scaled(ui->image_lb->width(), ui->image_lb->height(), Qt::KeepAspectRatio,
        Qt::SmoothTransformation);
    ui->image_lb->setPixmap(pixmap);
    ui->name_lb->setText(filename);

    has_image = true;
    SetGeoLabel(nx, ny);
}

void MainWindow::OnSaveBtn() {
    if (!has_image) {
        return;
    }

    auto filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".",
        tr("Image File (*.bmp, *.png, *.jpg)"));
    SaveImage(std::string(filename.toLocal8Bit())); // fix a bug here. (DON'T use toStdString)
}

void MainWindow::SetGeoLabel(int w, int h) {
    ui->geo_w_input->setText(QString::number(w));
    ui->geo_h_input->setText(QString::number(h));
}