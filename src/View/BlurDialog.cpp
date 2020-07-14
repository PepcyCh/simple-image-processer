#include "BlurDialog.h"

#include <QIntValidator>

BlurDialog::BlurDialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    InitBlurDialog();
}

BlurDialog::~BlurDialog() {
    delete ui;
}

void BlurDialog::InitBlurDialog() {

}
void BlurDialog::OnMedBtn(){

}
void BlurDialog::OnMeanBtn(){

}
void BlurDialog::OnGauBtn(){

}
void BlurDialog::OnBiBtn(){

}

void BlurDialog::accept() {
    QDialog::accept();
}