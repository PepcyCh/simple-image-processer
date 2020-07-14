#include <QApplication>

#include "appprocess.h"

int main(int argc, char **argv) { // RUN_APP
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication qapp(argc, argv);

    APP image_processer;
    image_processer.Run_APP();

    return qapp.exec();
}