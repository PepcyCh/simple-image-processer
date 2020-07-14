#pragma once

#include <QDialog>
#include "ui_BlurDialog.h"

class BlurDialog : public QDialog {
    Q_OBJECT

  public:
    BlurDialog(QWidget *parent = nullptr);
    ~BlurDialog();

    void accept() override;

  private:
    Ui::Dialog *ui;
  
    void InitBlurDialog();
    
  private slots:
    void OnMedBtn();
    void OnMeanBtn();
    void OnGauBtn();
    void OnBiBtn();

};