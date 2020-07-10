#pragma once

#include <vector>

#include "Image.h"

class ImageModel {
  public:
    Image PushImage(const Image &img);
    
    Image GetCurrent() const;
    Image GetPrevious() const;

    Image Undo();
    bool CanUndo() const;
    Image Redo();
    bool CanRedo() const;

    void Reset();

  private:
    std::vector<Image> images;
    int curr = 0;
};