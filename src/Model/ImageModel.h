#pragma once

#include <vector>

#include "Image.h"

class ImageModel {
  public:
    void PushImage(const Image &img);
    
    [[nodiscard]] const Image& GetCurrent() const;

    const Image& Undo();
    [[nodiscard]] bool CanUndo() const;
    const Image& Redo();
    [[nodiscard]] bool CanRedo() const;

    void Reset();

  private:
    std::vector<Image> images;
    int curr = 0;
};