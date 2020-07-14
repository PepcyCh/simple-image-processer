#include "BlurDialog.h"

#include <QIntValidator>

BlurDialog::BlurDialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    opt = -1 ;
    ui->setupUi(this);
    InitBlurDialog();
}

BlurDialog::~BlurDialog() {
    delete ui;
}

void BlurDialog::InitBlurDialog() {
        ui -> med_bs_input -> setText(QString::number(1)) ;
        ui -> mean_bs_input -> setText(QString::number(1)) ;
        ui -> gau_bs_input -> setText(QString::number(1)) ;
        ui -> bi_bs_input -> setText(QString::number(1)) ;

        ui -> med_tim_input -> setText(QString::number(1)) ;
        ui -> mean_tim_input -> setText(QString::number(1)) ;
        ui -> gau_tim_input -> setText(QString::number(1)) ;
        ui -> bi_tim_input -> setText(QString::number(1)) ;

        ui -> gau_sig_input -> setText(QString::number(1.0)) ;
        ui -> bi_s_input -> setText(QString::number(40)) ;
        ui -> bi_r_input -> setText(QString::number(12.5)) ;
}
void BlurDialog::OnMedBtn(){
        opt = 0;
        bs = ui -> med_bs_input -> text().toInt(), tim = ui -> med_tim_input -> text().toInt() ;
}
void BlurDialog::OnMeanBtn(){
        opt = 1 ;
        bs = ui -> med_bs_input -> text().toInt(), tim = ui -> med_tim_input -> text().toInt() ;
}
void BlurDialog::OnGauBtn(){
        opt = 2 ;
        bs = ui -> gau_bs_input -> text().toInt(), tim = ui -> gau_tim_input -> text().toInt() ;
        sigma[0] = ui -> gau_sig_input -> text().toDouble() ;
}
void BlurDialog::OnBiBtn(){
        opt = 3 ;
        bs = ui -> bi_bs_input -> text().toInt(), tim = ui -> bi_tim_input -> text().toInt() ;
        sigma[0] = ui -> bi_s_input -> text().toDouble() ;
        sigma[1] = ui -> bi_r_input -> text().toDouble() ;
}

void BlurDialog::accept() {
    emit SendParams(bs, tim, sigma[0], sigma[1]) ;
    QDialog::accept();
}