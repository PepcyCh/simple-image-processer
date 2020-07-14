#pragma once

#include <QDialog>
#include "ui_BlurDialog.h"

class BlurDialog : public QDialog {
    Q_OBJECT

  public:
    BlurDialog(QWidget *parent = nullptr);
    ~BlurDialog();

    void accept() override;

  signals:
    void SendParams(int opt, int block_size, int tim, double sigma_0, double sigma_1);

  private:
    Ui::Dialog *ui;
    int bs, tim ;
    double sigma[2] ;
    int opt ;   
    // 00 -> Median, 01 -> Means, 10 -> Gauss, 11 -> Bilateral

    void InitBlurDialog();
    
  private slots:
    void OnMedBtn();
    void OnMeanBtn();
    void OnGauBtn();
    void OnBiBtn();

};