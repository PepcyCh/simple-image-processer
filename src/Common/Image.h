#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Image {
  public:
    Image() = default;
    Image(size_t width, size_t height);
    Image(size_t width, size_t height, uint8_t *data, int n_channel);

    bool Empty() const;
    void Resize(size_t width, size_t height);
    void Clear(uint8_t value = 0);

    size_t GetWidth() const;
    size_t GetHeight() const;
    const uint8_t *GetData() const;

    uint8_t Get(int x, int y, int i) const;
    uint8_t GetR(int x, int y) const;
    uint8_t GetG(int x, int y) const;
    uint8_t GetB(int x, int y) const;
    uint8_t GetA(int x, int y) const;

    void SetColor(int x, int y, int i, uint8_t v);
    void SetColor(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    void SetColor(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    void SampleAt(double u, double v, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const;

  private:
    size_t width = 0;
    size_t height = 0;
    std::vector<uint8_t> data;
};