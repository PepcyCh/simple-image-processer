#include "AdapThresDialog.h"

#include <QIntValidator>

AdapThresDialog::AdapThresDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AdapThresDialog) {
    ui->setupUi(this);
    SetInputValidator();
}

AdapThresDialog::~AdapThresDialog() {
    delete ui;
}

void AdapThresDialog::SetInputValidator() {
    ui->radius_input->setValidator(new QIntValidator(1, 99, this));
    ui->bias_input->setValidator(new QIntValidator(-128, 127, this));
}

void AdapThresDialog::accept() {
    emit SendParams(ui->radius_input->text().toInt(), ui->bias_input->text().toInt());
    QDialog::accept();
}