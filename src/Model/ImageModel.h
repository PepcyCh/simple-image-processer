#pragma once

#include <vector>

#include "Image.h"

class ImageModel {
  public:
    void PushImage(const Image &img);
    
    [[nodiscard]] Image GetCurrent() const;
    [[nodiscard]] Image GetPrevious() const;

    Image Undo();
    [[nodiscard]] bool CanUndo() const;
    Image Redo();
    [[nodiscard]] bool CanRedo() const;

    void Reset();

  private:
    std::vector<Image> images;
    int curr = 0;
};