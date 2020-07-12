#include "ImageModel.h"

#include <cassert>

Image ImageModel::PushImage(const Image &img) {
    ++curr;
    if (curr == images.size()) {
        images.push_back(img);
    } else {
        images[curr] = img;
        images.resize(curr + 1);
    }
    return img;
}

Image ImageModel::GetCurrent() const {
    assert(!images.empty() && "call GetCurrent(), but images is empty");
    return images[curr];
}

Image ImageModel::GetPrevious() const {
    assert(!images.empty() && curr > 0 && "call GetPrevious(), but images is empty/current image is the first one");
    return images[curr - 1];
}

Image ImageModel::Undo() {
    assert(CanUndo() && "call Undo(), but can't undo");
    --curr;
    return images[curr];
}

bool ImageModel::CanUndo() const {
    return curr > 0;
}

Image ImageModel::Redo() {
    assert(CanRedo() && "call Redo(), but can't redo");
    ++curr;
    return images[curr];
}

bool ImageModel::CanRedo() const {
    return curr < images.size();
}

void ImageModel::Reset() {
    images.clear();
    curr = -1;
}