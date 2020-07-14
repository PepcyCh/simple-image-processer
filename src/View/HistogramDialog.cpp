#include "HistogramDialog.h"

HistogramDialog::HistogramDialog(QDialog *parent) : QDialog(parent), ui(new Ui::HistogramDialog) {
    ui->setupUi(this);
}

HistogramDialog::~HistogramDialog() {
    delete ui;
}

static void SetLabelImage(QLabel *label, const Image &img) {
    int nx = img.GetWidth();
    int ny = img.GetHeight();
    int nn = img.GetChannelCnt();
    const uint8_t *data = img.GetData();

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
    pixmap = pixmap.scaled(label->width(), label->height(), Qt::KeepAspectRatio,
                           Qt::SmoothTransformation);
    label->setPixmap(pixmap);
}

void HistogramDialog::SetImages(const std::array<Image, 4> &imgs) {
    SetLabelImage(ui->l_img_lb, imgs[0]);
    SetLabelImage(ui->r_img_lb, imgs[1]);
    SetLabelImage(ui->g_img_lb, imgs[2]);
    SetLabelImage(ui->b_img_lb, imgs[3]);
}