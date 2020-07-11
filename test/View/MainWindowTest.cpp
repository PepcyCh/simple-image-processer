#include <QApplication>

#include <iostream>

#include "MainWindow.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include "cassert"

struct Image {
    const uint8_t *data = nullptr;
    int nx, ny, nn;
};

int main(int argc, char **argv) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow w;
    Image img;
    w.BindLoadImage([&img](const std::string &filename, const uint8_t *&data, int &nx, int &ny, int &nn) {
        data = stbi_load(filename.c_str(), &nx, &ny, &nn, 0);
        img.data = data;
        img.nx = nx;
        img.ny = ny;
        img.nn = nn;
    });
    w.BindSaveImage([&img](const std::string &filename) {
        stbi_write_jpg(filename.c_str(), img.nx, img.ny, img.nn, img.data, 0);
    });
    w.show();

    return app.exec();
}