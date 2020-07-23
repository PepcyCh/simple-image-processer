#pragma once

#include <vector>
#include <memory>

#include "Image.h"

class ImageModel {
  public:
    Image *PushImage(Image &&img);
    
    [[nodiscard]] Image *GetCurrent() const;
    Image *Undo();
    [[nodiscard]] bool CanUndo() const;
    Image *Redo();
    [[nodiscard]] bool CanRedo() const;

    void Reset();

  private:
    std::vector<std::unique_ptr<Image>> images;
    int curr = 0;
};