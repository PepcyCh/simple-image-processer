#include <QApplication>

#include <iostream>

#include "MainWindow.h"
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

int main(int argc, char **argv) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow w;
    Image img;
    w.BindLoadImage([&img](const std::string &filename, Image &_img) {
        uint8_t *data = nullptr;
        int nx, ny, nn;
        data = stbi_load(filename.c_str(), &nx, &ny, &nn, 0);
        if (data != nullptr) {
            img = Image(nx, ny, data, nn);
        } else {
            img = Image(0, 0);
        }
        _img = img;
    });
    w.BindSaveImage([&img](const std::string &filename) {
        stbi_write_jpg(filename.c_str(), img.GetWidth(), img.GetHeight(), img.GetChannelCnt(), img.GetData(), 0);
    });
    w.show();

    return app.exec();
}