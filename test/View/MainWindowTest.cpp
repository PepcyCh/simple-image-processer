#include <QApplication>

#include <iostream>

#include "MainWindow.h"
#include "stb_image.h"
#include "stb_image_write.h"

int main(int argc, char **argv) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow w;
    w.BindLoadImage([](const std::string &filename, const uint8_t *&data, int &nx, int &ny, int &nn) {
        data = stbi_load(filename.c_str(), &nx, &ny, &nn, 0);
    });
    w.BindSaveImage([](const std::string &filename, const uint8_t *data, int nx, int ny, int nn) {
        stbi_write_jpg(filename.c_str(), nx, ny, nn, data, 0);
    });
    w.show();

    return app.exec();
}