#include "MainWindow.h"

#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    InitDialogs();
    InitShortcuts();
    InitValidators();
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
void MainWindow::BindUndoImage(const UndoImageTy &func) {
    UndoImage = func;
}
void MainWindow::BindRedoImage(const RedoImageTy &func) {
    RedoImage = func;
}

void MainWindow::BindGrayScale(const GrayScaleTy &func) {
    GrayScale = func;
}
void MainWindow::BindThreshold(const ThresholdTy &func) {
    Threshold = func;
}
void MainWindow::BindAdapThres(const AdapThresTy &func) {
    AdapThres = func;
}

void MainWindow::BindEqualization(const EqualizationTy &func) {
    Equalization = func;
}
void MainWindow::BindSharpen(const SharpenTy &func) {
    Sharpen = func ;
}
void MainWindow::BindBlur(const BlurTy &func) {
    Blur = func ;
}
void MainWindow::BindHistogram(const HistogramTy &func) {
    Histogram = func ;
}

void MainWindow::BindMeans(const MeansTy &func) {
    Means = func ;
}
void MainWindow::BindMedian(const MedianTy &func) {
    Median = func ;
}
void MainWindow::BindGauss(const GaussTy &func) {
    Gauss = func ;
}
void MainWindow::BindBilateral(const BilateralTy &func) {
    Bilateral = func ;
}

void MainWindow::BindScale(const ScaleTy &func) {
    Scale = func ;
}
void MainWindow::BindRotate(const RotateTy &func) {
    Rotate = func ;
}
void MainWindow::BindShearX(const ShearXTy &func) {
    ShearX = func ;
}
void MainWindow::BindShearY(const ShearYTy &func) {
    ShearY = func ;
}


void MainWindow::OnLoadBtn() {
    filename = QFileDialog::getOpenFileName(this, tr("Open Image"), ".",
        tr("Image File (*.bmp *.png *.jpg *.jpeg)"));
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
    filename = QFileDialog::getSaveFileName(this, tr("Save Image"), ".",
        tr("Image File (*.bmp *.png *.jpg *.jpeg)"));
    SaveImage(std::string(filename.toLocal8Bit())); // fix a bug here. (DON'T use toStdString)
    ui->name_lb->setText(filename);
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

void MainWindow::OnGrayScaleBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    GrayScale(shown_image);
    ShowImage();
}

void MainWindow::OnThresholdBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    Threshold(shown_image);
    ShowImage();
}

void MainWindow::OnAdapThresBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    if (adap_thres_dialog->exec() == QDialog::Accepted) {
        AdapThres(shown_image, params.block_size, params.bias);
        ShowImage();
    }
}

void MainWindow::OnEqualizationBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    Equalization(shown_image);
    ShowImage();
}

void MainWindow::OnSharpenBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    Sharpen(shown_image, 1);
    ShowImage();
}

void MainWindow::OnHistBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    std::array<Image, 4> imgs;
    Histogram(imgs);
    histogram_dialog->SetImages(imgs);
    histogram_dialog->exec();
}

void MainWindow::OnBlurBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    if (blur_dialog->exec() == QDialog::Accepted) {
        switch(BlurParams.opt) {
                case -1:
                        break ;
                case 0:
                        Median(shown_image, BlurParams.block_size, BlurParams.tim) ;
                        break ;
                case 1:
                        Means(shown_image, BlurParams.block_size, BlurParams.tim) ;
                        break ;
                case 2:
                        Gauss(shown_image, BlurParams.block_size, BlurParams.sigma[0], BlurParams.tim) ;
                        break ;
                case 3:
                        Bilateral(shown_image, BlurParams.block_size, BlurParams.sigma[0], BlurParams.sigma[1], BlurParams.tim) ;
                        break ;
                default:
                        break ;
        }
        ShowImage();
    }
}

void MainWindow::OnGeoWBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    double w = shown_image.GetWidth(), w_ = ui -> geo_w_input -> text().toInt() ;
    Scale(shown_image, 1.0, w_ / w ) ;
    ShowImage() ;
}
void MainWindow::OnGeoHBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    double h = shown_image.GetHeight(), h_ = ui -> geo_h_input -> text().toInt() ;
    Scale(shown_image, h_ / h, 1.0) ;
    ShowImage() ;
}

void MainWindow::OnRotBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    double ang = ui -> rot_input -> text().toInt() ;
    Rotate(shown_image, ang) ;
    ShowImage() ;
}
void MainWindow::OnShrXBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    double dx = ui -> shr_x_input -> text().toInt() ;
    ShearX(shown_image, dx) ;
    ShowImage() ;
}
void MainWindow::OnShrYBtn() {
    if (!has_image || shown_image.Empty()) {
        return;
    }
    double dy = ui -> shr_y_input -> text().toInt() ;
    ShearY(shown_image, dy) ;
    ShowImage() ;
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

void MainWindow::InitDialogs() {
    adap_thres_dialog = std::make_unique<AdapThresDialog>();
    connect(adap_thres_dialog.get(), &AdapThresDialog::SendParams,
            this, &MainWindow::SetAdapThresParams);

    histogram_dialog = std::make_unique<HistogramDialog>();
    blur_dialog = std::make_unique<BlurDialog>();
    connect(blur_dialog.get(), &BlurDialog::SendParams,
            this, &MainWindow::SetBlurParams);
}

void MainWindow::InitShortcuts() {
    ui->load_btn->setShortcut(QKeySequence::Open);
    ui->save_btn->setShortcut(QKeySequence::Save);
    ui->undo_btn->setShortcut(QKeySequence::Undo);
    ui->redo_btn->setShortcut(QKeySequence::Redo);
}

void MainWindow::InitValidators() {
    ui->geo_w_input->setValidator(new QIntValidator(1, 9999, this));
    ui->geo_h_input->setValidator(new QIntValidator(1, 9999, this));
    ui->rot_input->setValidator(new QIntValidator(-180, 180, this));
    ui->shr_x_input->setValidator(new QIntValidator(-999, 999, this));
    ui->shr_y_input->setValidator(new QIntValidator(-999, 999, this));
}

void MainWindow::SetAdapThresParams(int block_size, int bias) {
    params.block_size = block_size;
    params.bias = bias;
}
void MainWindow::SetBlurParams(int opt, int block_size, int tim, double sigma_0, double sigma_1) {
    BlurParams.opt = opt ;
    BlurParams.block_size = block_size ;
    BlurParams.tim = tim ;
    BlurParams.sigma[0] = sigma_0 ;
    BlurParams.sigma[1] = sigma_1 ;
}