#include "Image.h"

#include <algorithm>
#include <cmath>

Image::Image(size_t width, size_t height) : width(width), height(height) {
    data.resize(width * height * 4);
    std::fill(data.begin(), data.end(), 0);
}

Image::Image(size_t width, size_t height, uint8_t *data, int n_channel) {
    if (n_channel == 3 || n_channel == 4) {
        this->width = width;
        this->height = height;
        this->data.resize(width * height * 4);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                size_t id0 = 4 * (i * width + j);
                size_t id1 = n_channel * (i * width + j);
                this->data[id0] = data[id1];
                this->data[id0 + 1] = data[id1 + 1];
                this->data[id0 + 2] = data[id1 + 2];
                this->data[id0 + 3] = (n_channel == 4 ? data[id1 + 3] : 255);
            }
        }
    } else {
        this->width = 0;
        this->height = 0;
        this->data.resize(0);
    }
}

bool Image::Empty() const { return data.empty(); }

void Image::Resize(size_t width, size_t height) {
    data.clear();
    data.resize(width * height * 4);
    this->width = width;
    this->height = height;
    std::fill(data.begin(), data.end(), 0);
}

void Image::Clear(uint8_t value) {
    std::fill(data.begin(), data.end(), value);
}

size_t Image::GetWidth() const { return width; }
size_t Image::GetHeight() const { return height; }
const uint8_t *Image::GetData() const { return data.data(); }

uint8_t Image::Get(int x, int y, int i) const {
    if (i == 3 && (x < 0 || y < 0 || x >= height || y >= width)) return 0;
    x = std::clamp<int>(x, 0, height - 1);
    y = std::clamp<int>(y, 0, width - 1);
    return data[(x * width + y) * 4 + i];
}

uint8_t Image::GetR(int x, int y) const {
    x = std::clamp<int>(x, 0, height - 1);
    y = std::clamp<int>(y, 0, width - 1);
    return data[(x * width + y) * 4];
}
uint8_t Image::GetG(int x, int y) const {
    x = std::clamp<int>(x, 0, height - 1);
    y = std::clamp<int>(y, 0, width - 1);
    return data[(x * width + y) * 4 + 1];
}
uint8_t Image::GetB(int x, int y) const {
    x = std::clamp<int>(x, 0, height - 1);
    y = std::clamp<int>(y, 0, width - 1);
    return data[(x * width + y) * 4 + 2];
}
uint8_t Image::GetA(int x, int y) const {
    if (x < 0 || y < 0 || x >= height || y >= width) return 0;
    return data[(x * width + y) * 4 + 3];
}

void Image::SetColor(int x, int y, int i, uint8_t v) {
    if (x < 0 || y < 0 || x >= height || y >= width) return;
    data[(x * width + y) * 4 + i] = v;
}

void Image::SetColor(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x < 0 || y < 0 || x >= height || y >= width) return;
    size_t id = (x * width + y) * 4;
    data[id] = r;
    data[id + 1] = g;
    data[id + 2] = b;
    data[id + 3] = 255;
}

void Image::SetColor(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    if (x < 0 || y < 0 || x >= height || y >= width) return;
    size_t id = (x * width + y) * 4;
    data[id] = r;
    data[id + 1] = g;
    data[id + 2] = b;
    data[id + 3] = a;
}

void Image::SampleAt(double u, double v, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const {
    float tu = u * height;
    float tv = v * width;

    int su[2];
    su[0] = round(tu) - 1;
    su[1] = su[0] + 1;
    double du = tu - 0.5 - su[0];

    int sv[2];
    sv[0] = round(tv) - 1;
    sv[1] = sv[0] + 1;
    double dv = tv - 0.5 - sv[0];

    double tres[4];
    for (int c = 0; c < 4; c++) {
        double sum = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                uint8_t t = Get(su[i], sv[j], c);
                double alpha = (c == 3 ? 1 : Get(su[i], sv[j], 3) / 255.0);
                sum += t * alpha * (i * du + (1 - i) * (1 - du)) * (j * dv + (1 - j) * (1 - dv));
            }
        }
        tres[c] = sum;
    }
    if (tres[3]) {
        tres[0] /= tres[3] / 255.;
        tres[1] /= tres[3] / 255.;
        tres[2] /= tres[3] / 255.;
    }

    r = tres[0];
    g = tres[1];
    b = tres[2];
    a = tres[3];
}