#include "BlurDialog.h"

#include <QIntValidator>
#include <QDoubleValidator>

BlurDialog::BlurDialog(QWidget *parent) : QDialog(parent), ui(new Ui::BlurDialog) {
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

        ui -> med_bs_input -> setValidator(new QIntValidator(1, 49, this)) ;
        ui -> mean_bs_input -> setValidator(new QIntValidator(1, 49, this)) ;
        ui -> gau_bs_input -> setValidator(new QIntValidator(1, 49, this)) ;
        ui -> bi_bs_input -> setValidator(new QIntValidator(1, 49, this)) ;

        ui -> med_tim_input -> setValidator(new QIntValidator(1, 5, this));
        ui -> mean_tim_input -> setValidator(new QIntValidator(1, 5, this));
        ui -> gau_tim_input -> setValidator(new QIntValidator(1, 5, this));
        ui -> bi_tim_input -> setValidator(new QIntValidator(1, 5, this));

        ui -> gau_sig_input -> setValidator(new QDoubleValidator(0, 99999.99, 2, this));
        ui -> bi_s_input -> setValidator(new QDoubleValidator(0, 99999.99, 2, this));
        ui -> bi_r_input -> setValidator(new QDoubleValidator(0, 99999.99, 2, this));
}
void BlurDialog::OnMedBtn(){
        opt = 0;
        bs = ui -> med_bs_input -> text().toInt(), tim = ui -> med_tim_input -> text().toInt() ;
        accept();
}
void BlurDialog::OnMeanBtn(){
        opt = 1 ;
        bs = ui -> mean_bs_input -> text().toInt(), tim = ui -> mean_tim_input -> text().toInt() ;
        accept();
}
void BlurDialog::OnGauBtn(){
        opt = 2 ;
        bs = ui -> gau_bs_input -> text().toInt(), tim = ui -> gau_tim_input -> text().toInt() ;
        sigma[0] = ui -> gau_sig_input -> text().toDouble() ;
        accept();
}
void BlurDialog::OnBiBtn(){
        opt = 3 ;
        bs = ui -> bi_bs_input -> text().toInt(), tim = ui -> bi_tim_input -> text().toInt() ;
        sigma[0] = ui -> bi_s_input -> text().toDouble() ;
        sigma[1] = ui -> bi_r_input -> text().toDouble() ;
        accept();
}

void BlurDialog::accept() {
    emit SendParams(opt, bs, tim, sigma[0], sigma[1]) ;
    QDialog::accept();
}