#pragma once

#include <QDialog>
#include "ui_AdapThresDialog.h"

class AdapThresDialog : public QDialog {
    Q_OBJECT

  public:
    AdapThresDialog(QWidget *parent = nullptr);
    ~AdapThresDialog();

    void accept() override;

  signals:
    void SendParams(int block_size, int bias);

  private:
    Ui::AdapThresDialog *ui;

    void SetInputValidator();
};