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

void MainWindow::BindUndoImage(const MainWindow::UndoImageTy &func) {
    UndoImage = func;
}

void MainWindow::BindRedoImage(const MainWindow::RedoImageTy &func) {
    RedoImage = func;
}

void MainWindow::OnLoadBtn() {
    auto filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
        tr("Image File (*.bmp *.png *.jpg *jpeg)"));
    std::string s = std::string(filename.toLocal8Bit()); // fix a bug here. (DON'T use toStdString)
    LoadImage(s, shown_image);
    if (shown_image.Empty()) {
        return;
    }
    ShowImage();
    has_image = true;
}

void MainWindow::OnSaveBtn() {
    if (!has_image) {
        return;
    }

    auto filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".",
        tr("Image File (*.bmp *.png *.jpg *jpeg)"));
    SaveImage(std::string(filename.toLocal8Bit())); // fix a bug here. (DON'T use toStdString)
}

void MainWindow::OnUndoBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    UndoImage(shown_image);
    ShowImage();
}

void MainWindow::OnRedoBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    RedoImage(shown_image);
    ShowImage();
}

void MainWindow::SetGeoLabel(int w, int h) {
    ui->geo_w_input->setText(QString::number(w));
    ui->geo_h_input->setText(QString::number(h));
}

void MainWindow::ShowImage() {
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
    SetGeoLabel(nx, ny);
}

