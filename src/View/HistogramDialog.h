#pragma once

#include <array>

#include <QDialog>
#include "ui_HistogramDialog.h"

#include "Image.h"

class HistogramDialog : public QDialog {
  public:
    HistogramDialog(QDialog *parent = nullptr);
    ~HistogramDialog();

    void SetImages(const std::array<Image, 4> &imgs);

  private:
    Ui::HistogramDialog *ui;
};