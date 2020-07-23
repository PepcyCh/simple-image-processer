#include "ImageModel.h"

#include <cassert>

Image *ImageModel::PushImage(Image &&img) {
    ++curr;
    auto pimg = std::make_unique<Image>(std::move(img));
    if (curr == images.size()) {
        images.push_back(std::move(pimg));
    } else {
        images[curr] = std::move(pimg);
        images.resize(curr + 1);
    }
    return images[curr].get();
}

Image *ImageModel::GetCurrent() const {
    assert(!images.empty() && "call GetCurrent(), but images is empty");
    return images[curr].get();
}

Image *ImageModel::Undo() {
    assert(CanUndo() && "call Undo(), but can't undo");
    --curr;
    return images[curr].get();
}

bool ImageModel::CanUndo() const {
    return curr > 0;
}

Image *ImageModel::Redo() {
    assert(CanRedo() && "call Redo(), but can't redo");
    ++curr;
    return images[curr].get();
}

bool ImageModel::CanRedo() const {
    return curr + 1 < images.size();
}

void ImageModel::Reset() {
    images.clear();
    curr = -1;
}