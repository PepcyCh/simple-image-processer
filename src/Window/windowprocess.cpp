//
// Created by Filene on 2020/7/11.
//
#include "windowprocess.h"


int funcss(int argc, char **argv){
    QApplication a(argc, argv);

    auto window = new QDialog;
    window->setWindowTitle("Enter your Age");

    auto spinBox = new QSpinBox;
    auto slider = new QSlider(Qt::Horizontal);  //水平
    spinBox->setRange(0,130);
    slider->setRange(0,130);

    QObject::connect(spinBox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    QObject::connect(slider,SIGNAL(valueChanged(int)),spinBox,SLOT(setValue(int)));

    auto layout = new QHBoxLayout;
    layout->addWidget(spinBox);
    layout->addWidget(slider);
    window->setLayout(layout);

    window->show();

    return a.exec();
}