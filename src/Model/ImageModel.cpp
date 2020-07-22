#include "ImageModel.h"

#include <cassert>

void ImageModel::PushImage(const Image &img) {
    ++curr;
    if (curr == images.size()) {
        images.push_back(img);
    } else {
        images[curr] = img; // need to copy.
        images.resize(curr + 1);
    }
    // return img;
}

const Image& ImageModel::GetCurrent() const {
    assert(!images.empty() && "call GetCurrent(), but images is empty");
    return images[curr];
}

const Image& ImageModel::Undo() {
    assert(CanUndo() && "call Undo(), but can't undo");
    --curr;
    return images[curr];
}

bool ImageModel::CanUndo() const {
    return curr > 0;
}

const Image& ImageModel::Redo() {
    assert(CanRedo() && "call Redo(), but can't redo");
    ++curr;
    return images[curr];
}

bool ImageModel::CanRedo() const {
    return curr + 1 < images.size();
}

void ImageModel::Reset() {
    images.clear();
    curr = -1;
}