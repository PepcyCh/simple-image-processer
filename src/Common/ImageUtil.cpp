#include "ImageUtil.h"

#include <cmath>
#include <iostream>
#include <algorithm>

#include "MathUtil.h"

Image ImageUtil::RGB2YUV(const Image &img) {
    Image res(img.GetWidth(), img.GetHeight());
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t Y = 0.299 * img.GetR(i, j) + 0.587 * img.GetG(i, j) + 0.114 * img.GetB(i, j);
            uint8_t U = -0.169 * img.GetR(i, j) - 0.331 * img.GetG(i, j) + 0.5 * img.GetB(i, j) + 128;
            uint8_t V = 0.5 * img.GetR(i, j) - 0.419 * img.GetG(i, j) - 0.081 * img.GetB(i, j) + 128;
            res.SetColor(i, j, Y, U, V, img.GetA(i, j));
        }
    }

    return res;
}

Image ImageUtil::YUV2RGB(const Image &img) {
    Image res(img.GetWidth(), img.GetHeight());
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t R = std::clamp(img.GetR(i, j) - 0.00093 * (img.GetG(i, j) - 128) +
                1.401687 * (img.GetB(i, j) - 128), 0.0, 255.0);
            uint8_t G = std::clamp(img.GetR(i, j) - 0.3437 * (img.GetG(i, j) - 128) -
                0.71417 * (img.GetB(i, j) - 128), 0.0, 255.0);
            uint8_t B = std::clamp(img.GetR(i, j) + 1.77216 * (img.GetG(i, j) - 128) +
                0.00099 * (img.GetB(i, j) - 128), 0.0, 255.0);
            res.SetColor(i, j, R, G, B, img.GetA(i, j));
        }
    }

    return res;
}

Image ImageUtil::RGB2Lab(const Image &img) {
    auto reduce = [](double x) {
        return (x > 0.04045 ? pow((x + 0.055) / 1.055, 2.4) : x / 12.92) * 100.0;
    };
    auto f = [](double x) {
        double d = 6.0 / 29.0;
        return (x > d * d * d) ? pow(x, 1.0 / 3.0) : x / (3 * d * d) + 4.0 / 29.0;
    };

    Image res(img.GetWidth(), img.GetHeight());
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            double R = reduce(img.GetR(i, j) / 255.0);
            double G = reduce(img.GetG(i, j) / 255.0);
            double B = reduce(img.GetB(i, j) / 255.0);

            double X = 0.4124 * R + 0.3576 * G + 0.1805 * B;
            double Y = 0.2126 * R + 0.7152 * G + 0.0722 * B;
            double Z = 0.0193 * R + 0.1192 * G + 0.9505 * B;
            X /= 95.047;
            Y /= 100.0;
            Z /= 108.883;

            double fY = f(Y);
            double L = 116 * fY - 16;

            double fX = f(X);
            double a = 500 * (fX - fY);

            double fZ = f(Z);
            double b = 200 * (fY - fZ);

            res.SetColor(i, j, std::clamp(L * 2.55, 0.0, 255.0),
                               std::clamp(a + 128, 0.0, 255.0),
                               std::clamp(b + 128, 0.0, 255.0),
                               img.GetA(i, j));
        }
    }
    return res;
}

Image ImageUtil::Lab2RGB(const Image &img) {
    auto correct = [](double x) {
        return x > 0.0031308 ? 1.055 * pow(x, 1.0 / 2.4) - 0.055 : 12.92 * x;
    };
    auto f = [](double x) {
        double d = 6.0 / 29.0;
        return (x > d) ? (x * x * x) : (3 * d * d * (x - 4.0 / 29.0));
    };

    Image res(img.GetWidth(), img.GetHeight());
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            double L = img.Get(i, j, 0) / 2.55;
            double a = img.Get(i, j, 1) - 128.0;
            double b = img.Get(i, j, 2) - 128.0;

            double tY = (L + 16) / 116;

            double Y = f(tY);
            double X = f(tY + a / 500);
            double Z = f(tY - b / 200);

            X *= 0.95047;
            Y *= 1.0;
            Z *= 1.08883;

            double R = correct(3.2406 * X - 1.5372 * Y - 0.4986 * Z);
            double G = correct(-0.9689 * X + 1.8758 * Y + 0.0415 * Z);
            double B = correct(0.0557 * X - 0.2040 * Y + 1.0570 * Z);

            res.SetColor(i, j, std::clamp(255 * R, 0.0, 255.0),
                               std::clamp(255 * G, 0.0, 255.0),
                               std::clamp(255 * B, 0.0, 255.0),
                               img.GetA(i, j));
        }
    }
    return res;
}

Image ImageUtil::GrayScale(const Image &img) {
    Image res(img.GetWidth(), img.GetHeight());
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t Y = 0.299 * img.GetR(i, j) + 0.587 * img.GetG(i, j) + 0.114 * img.GetB(i, j);
            res.SetColor(i, j, Y, Y, Y, img.GetA(i, j));
        }
    }

    return res;
}

Image ImageUtil::OtsuThreshold(const Image &img) {
    Image res = GrayScale(img);

    int cnt[256];
    std::fill(cnt, cnt + 256, 0);
    for (int i = 0; i < res.GetHeight(); i++) {
        for (int j = 0; j < res.GetWidth(); j++) {
            ++cnt[res.GetR(i, j)];
        }
    }

    int N = res.GetHeight() * res.GetWidth();
    double omega[256], mu[256];
    for (int i = 0; i < 256; i++) {
        double p = (double) cnt[i] / N;
        omega[i] = (i ? omega[i - 1] : 0) + p;
        mu[i] = (i ? mu[i - 1] : 0) + i * p;
    }

    double max_val = 0;
    int threshold = -1;
    for (int i = 0; i < 255; i++) {
        double sigma_b = (mu[255] * omega[i] - mu[i]) * (mu[255] * omega[i] - mu[i]) / (omega[i] * (1 - omega[i]));
        if (sigma_b > max_val) {
            max_val = sigma_b;
            threshold = i;
        }
    }

    for (int i = 0; i < res.GetHeight(); i++) {
        for (int j = 0; j < res.GetWidth(); j++) {
            uint8_t c = (res.GetR(i, j) > threshold ? 255 : 0);
            res.SetColor(i, j, c, c, c);
        }
    }

    return res;
}

Image ImageUtil::AdaptiveThreshold(const Image &img, int block_size, AdaptiveThresholdMethod method,
        double minus, double sx, double sy) {
    block_size >>= 1;

    Image temp = GrayScale(img);
    Image res(img.GetWidth(), img.GetHeight());

    Kernel kernel;
    if (method == MEAN) {
        kernel.Create(block_size << 1 | 1, block_size << 1 | 1, 1);
    } else {
        kernel = GetGaussian2D(block_size << 1 | 1, block_size << 1 | 1, sx, sy);
    }

    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            double sum = 0;
            double cnt = 0;
            int xl = std::max<int>(0, i - block_size);
            int xr = std::min<int>(img.GetHeight(), i + block_size);
            for (int x = xl; x <= xr; x++) {
                int yl = std::max<int>(0, j - block_size);
                int yr = std::min<int>(img.GetWidth(), j + block_size);
                for (int y = yl; y <= yr; y++) {
                    sum += kernel[block_size + x - i][block_size + y - j] * temp.Get(x, y, 0);
                    cnt += kernel[block_size + x - i][block_size + y - j];
                }
            }
            sum = sum / cnt - minus;
            uint8_t value = temp.Get(i, j, 0) >= sum ? 255 : 0;
            res.SetColor(i, j, value, value, value);
        }
    }

    return res;
}

Image ImageUtil::Erode(const Image &img, const Kernel &kernel, int anchor_x, int anchor_y, int iteration) {
    if (anchor_x < 0 || anchor_x >= kernel.Rows()) anchor_x = 0;
    if (anchor_y < 0 || anchor_y >= kernel.Cols()) anchor_y = 0;

    Image res(img.GetWidth(), img.GetHeight()), timg = img;
    for (int tim = 0; tim < iteration; tim++) {
        for (int i = 0; i < img.GetHeight(); i++) {
            for (int j = 0; j < img.GetWidth(); j++) {
                uint8_t c[4] = {255, 255, 255, timg.Get(i, j, 3)};
                for (int x = 0; x < kernel.Rows(); x++) {
                    for (int y = 0; y < kernel.Cols(); y++) {
                        if (kernel[x][y]) {
                            int ux = i + (x - anchor_x);
                            int uy = j + (y - anchor_y);
                            for (int k = 0; k < 3; k++) {
                                c[k] = std::min(c[k], timg.Get(ux, uy, k));
                            }
                        }
                    }
                }
                res.SetColor(i, j, c[0], c[1], c[2], c[3]);
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Dilate(const Image &img, const Kernel &kernel, int anchor_x, int anchor_y, int iteration) {
    if (anchor_x < 0 || anchor_x >= kernel.Rows()) anchor_x = 0;
    if (anchor_y < 0 || anchor_y >= kernel.Cols()) anchor_y = 0;

    Image res(img.GetWidth(), img.GetHeight()), timg = img;
    for (int tim = 0; tim < iteration; tim++) {
        for (int i = 0; i < img.GetHeight(); i++) {
            for (int j = 0; j < img.GetWidth(); j++) {
                uint8_t c[4] = {0, 0, 0, timg.Get(i, j, 3)};
                for (int x = 0; x < kernel.Rows(); x++) {
                    for (int y = 0; y < kernel.Cols(); y++) {
                        if (kernel[x][y]) {
                            int ux = i + (x - anchor_x);
                            int uy = j + (y - anchor_y);
                            for (int k = 0; k < 3; k++) {
                                c[k] = std::max(c[k], timg.Get(ux, uy, k));
                            }
                        }
                    }
                }
                res.SetColor(i, j, c[0], c[1], c[2], c[3]);
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Open(const Image &img, const Kernel &kernel, int anchor_x, int anchor_y, int iteration) {
    Image res = Erode(img, kernel, anchor_x, anchor_y, iteration);
    res = Dilate(res, kernel, anchor_x, anchor_y, iteration);
    return res;
}

Image ImageUtil::Close(const Image &img, const Kernel &kernel, int anchor_x, int anchor_y, int iteration) {
    Image res = Dilate(img, kernel, anchor_x, anchor_y, iteration);
    res = Erode(res, kernel, anchor_x, anchor_y, iteration);
    return res;
}

Kernel ImageUtil::GetGaussian1D(int length, double sigma) {
    length >>= 1;
    Kernel res(length << 1 | 1, 1, 0);
    sigma *= sigma;
    double sum = 0;
    for (int i = -length; i <= length; i++) {
        res[i + length][0] = std::exp(-i * i / 2.0 / sigma);
        sum += res[i + length][0];
    }
    return res / sum;
}

Kernel ImageUtil::GetGaussian2D(int width, int height, double sigma_x, double sigma_y) {
    width >>= 1;
    height >>= 1;
    return GetGaussian1D(height << 1 | 1, sigma_x) * GetGaussian1D(width << 1 | 1, sigma_y).Transposed();
}

Image ImageUtil::Means(const Image &img, int block_size, int iteration) {
    block_size >>= 1;

    Image res(img), timg(img);
    for (int tim = 0; tim < iteration; tim++) {
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < img.GetHeight(); i++) {
                for (int j = 0; j < img.GetWidth(); j++) {
                    int cnt = 0, sum = 0;
                    int xl = std::max(0, i - block_size);
                    int xr = std::min<int>(i + block_size, img.GetHeight() - 1);
                    for (int x = xl; x <= xr; x++) {
                        int yl = std::max(0, j - block_size);
                        int yr = std::min<int>(j + block_size, img.GetWidth() - 1);
                        for (int y = yl; y <= yr; y++) {
                            ++cnt;
                            sum += timg.Get(x, y, c);
                        }
                    }
                    uint8_t col = round((double) sum / cnt);
                    res.SetColor(i, j, c, col);
                }
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Median(const Image &img, int block_size, int iteration) {
    block_size >>= 1;
    std::vector<uint8_t> values((2 * block_size + 1) * (2 * block_size + 1));

    Image res(img), timg(img);
    for (int tim = 0; tim < iteration; tim++) {
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < img.GetHeight(); i++) {
                for (int j = 0; j < img.GetWidth(); j++) {
                    int cnt = 0;
                    int xl = std::max(0, i - block_size);
                    int xr = std::min<int>(i + block_size, img.GetHeight() - 1);
                    for (int x = xl; x <= xr; x++) {
                        int yl = std::max(0, j - block_size);
                        int yr = std::min<int>(j + block_size, img.GetWidth() - 1);
                        for (int y = yl; y <= yr; y++) {
                            values[cnt] = timg.Get(x, y, c);
                            ++cnt;
                        }
                    }
                    std::nth_element(values.begin(), values.begin() + cnt / 2, values.begin() + cnt);
                    uint8_t col = values[cnt / 2];
                    res.SetColor(i, j, c, col);
                }
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Gaussian(const Image &img, int block_size, double sigma, int iteration) {
    auto kernel = GetGaussian2D(block_size, block_size, sigma, sigma);
    block_size >>= 1;

    Image res(img), timg(img);
    for (int tim = 0; tim < iteration; tim++) {
        for (int c = 0; c < 3; c++) {
            for (int i = 0; i < img.GetHeight(); i++) {
                for (int j = 0; j < img.GetWidth(); j++) {
                    double cnt = 0, sum = 0;
                    int xl = std::max(0, i - block_size);
                    int xr = std::min<int>(i + block_size, img.GetHeight() - 1);
                    for (int x = xl; x <= xr; x++) {
                        int yl = std::max(0, j - block_size);
                        int yr = std::min<int>(j + block_size, img.GetWidth() - 1);
                        for (int y = yl; y <= yr; y++) {
                            cnt += kernel[x - i + block_size][y - j + block_size];
                            sum += kernel[x - i + block_size][y - j + block_size] * timg.Get(x, y, c);
                        }
                    }
                    uint8_t col = round(sum / cnt);
                    res.SetColor(i, j, c, col);
                }
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Laplacian(const Image &img, double C) {
    Image res(img);

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < img.GetHeight(); i++) {
            for (int j = 0; j < img.GetWidth(); j++) {
                int lap = img.Get(i - 1, j, c) + img.Get(i + 1, j, c)
                        + img.Get(i, j - 1, c) + img.Get(i, j + 1, c)
                        - 4 * img.Get(i, j, c);
                uint8_t col = std::clamp(img.Get(i, j, c) - C * lap, 0., 255.);
                res.SetColor(i, j, c, col);
            }
        }
    }

    return res;
}

Image ImageUtil::Bilateral(const Image &img, int block_size, double sigma_s, double sigma_r, int iteration) {
    auto kernel = GetGaussian2D(block_size, block_size, sigma_s, sigma_s);
    block_size >>= 1;

    Image res(img), timg(img);
    for (int tim = 0; tim < iteration; tim++) {
        for (int i = 0; i < img.GetHeight(); i++) {
            for (int j = 0; j < img.GetWidth(); j++) {
                double cnt = 0;
                double sum[3] = {0, 0, 0};
                uint8_t r = timg.GetR(i, j), g = timg.GetG(i, j), b = timg.GetB(i, j);
                int xl = std::max(0, i - block_size);
                int xr = std::min<int>(i + block_size, img.GetHeight() - 1);
                for (int x = xl; x <= xr; x++) {
                    int yl = std::max(0, j - block_size);
                    int yr = std::min<int>(j + block_size, img.GetWidth() - 1);
                    for (int y = yl; y <= yr; y++) {
                        double col_dist_sqr = (r - timg.GetR(x, y)) * (r - timg.GetR(x, y))
                                            + (g - timg.GetG(x, y)) * (g - timg.GetG(x, y))
                                            + (b - timg.GetB(x, y)) * (b - timg.GetB(x, y));

                        double gcol = MathUtil::GaussSqr(col_dist_sqr, sigma_r);
                        double gspc = kernel[x - i + block_size][y - j + block_size];
                        cnt += gcol * gspc;
                        for (int c = 0; c < 3; c++)
                            sum[c] += gcol * gspc * timg.Get(x, y, c);
                    }
                }
                for (int c = 0; c < 3; c++) {
                    uint8_t col = std::clamp(sum[c] / cnt, 0., 255.);
                    res.SetColor(i, j, c, col);
                }
            }
        }
        timg = res;
    }

    return res;
}

Image ImageUtil::Logarithm(const Image &img) {
    Image res = RGB2Lab(img);

    int max_l = 0;
    for (int i = 0; i < res.GetHeight(); i++) {
        for (int j = 0; j < res.GetWidth(); j++) {
            max_l = std::max<int>(max_l, res.GetR(i, j));
        }
    }

    double denominator = 255.0 / log(max_l / 255.0 + 1);
    for (int i = 0; i < res.GetHeight(); i++) {
        for (int j = 0; j < res.GetWidth(); j++) {
            double numerator = log(res.GetR(i, j) / 255.0 + 1);
            uint8_t c = (uint8_t) round(numerator * denominator);
            res.SetColor(i, j, 0, c);
        }
    }

    res = Lab2RGB(res);
    return res;
}

std::vector<double> ImageUtil::GetHistogram(const Image &img) {
    std::vector<double> hist(256, 0);
    Image res = RGB2YUV(img);
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            ++hist[res.GetR(i, j)];
        }
    }
    int N = img.GetWidth() * img.GetHeight();
    for (auto &i : hist) {
        i /= N;
    }
    return hist;
}

std::vector<double> ImageUtil::GetHistogram(const Image &img, int cid) {
    std::vector<double> hist(256, 0);
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            ++hist[img.Get(i, j, cid)];
        }
    }
    int N = img.GetWidth() * img.GetHeight();
    for (auto &i : hist) {
        i /= N;
    }
    return hist;
}

Image ImageUtil::HistogramEqualize(const Image &img) {
    Image res = RGB2Lab(img);

    auto hist = GetHistogram(res, 0);
    double s[256];
    for (int i = 0; i < 256; i++) {
        s[i] = (i ? s[i - 1] : 0) + hist[i];
    }

     for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t col = round(s[res.Get(i, j, 0)] * 255);
            res.SetColor(i, j, 0, col);
        }
    }

    res = Lab2RGB(res);
    return res;
}

Image ImageUtil::HistogramFit(const Image &img, const std::vector<double> &hist) {
    Image res = RGB2Lab(img);
    res = HistogramFit(res, hist, 0);
    res = Lab2RGB(res);
    return res;
}

Image ImageUtil::HistogramFit(const Image &img, const std::vector<double> &hist, int cid) {
    Image res = img;

    auto h = GetHistogram(img, cid);
    double s[256], t[256];
    for (int i = 0; i < 256; i++) {
        s[i] = (i ? s[i - 1] : 0) + h[i];
        t[i] = (i ? t[i - 1] : 0) + hist[i];
    }

    int map[256];
    for (int si = 0, ti = 0; si < 256; si++) {
        while (ti < 256 && s[si] > t[ti]) ++ti;
        if (ti == 256) {
            map[si] = 255;
        } else if (ti == 0) {
            map[si] = 0;
        } else {
            map[si] = ti - (std::abs(s[si] - t[ti - 1]) < std::abs(s[si] - t[ti]));
        }
    }

    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t col = map[res.Get(i, j, cid)];
            res.SetColor(i, j, cid, col);
        }
    }

    return res;
}

Image ImageUtil::Curve(const Image &img, const std::vector<std::pair<int, int>> &points) {
    Image res = RGB2Lab(img);
    res = Curve(res, points, 0);
    res = Lab2RGB(res);
    return res;
}

Image ImageUtil::Curve(const Image &img, const std::vector<std::pair<int, int>> &points, int cid) {
    Image res = img;
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            int f = MathUtil::Interpolate(points, img.Get(i, j, cid));
            res.SetColor(i, j, cid, std::clamp(f, 0, 255));
        }
    }
    return res;
}

std::pair<int, int> ImageUtil::Adjust(Image &img) {
    int ax = 0;
    for (int i = 0; i < img.GetHeight(); i++) {
        bool flag = true;
        for (int j = 0; j < img.GetWidth(); j++) {
            if (img.GetA(i, j)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++ax;
        } else {
            break;
        }
    }
    int ay = 0;
    for (int i = 0; i < img.GetWidth(); i++) {
        bool flag = true;
        for (int j = 0; j < img.GetHeight(); j++) {
            if (img.GetA(j, i)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++ay;
        } else {
            break;
        }
    }
    int bx = 0;
    for (int i = img.GetHeight() - 1; i >= ax; i--) {
        bool flag = true;
        for (int j = 0; j < img.GetWidth(); j++) {
            if (img.GetA(i, j)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++bx;
        } else {
            break;
        }
    }
    int by = 0;
    for (int i = img.GetWidth() - 1; i >= ay; i--) {
        bool flag = true;
        for (int j = 0; j < img.GetHeight(); j++) {
            if (img.GetA(j, i)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ++by;
        } else {
            break;
        }
    }

    Image temp(img.GetWidth() - ay - by, img.GetHeight() - ax - bx);
    for (int i = 0; i < temp.GetHeight(); i++) {
        for (int j = 0; j < temp.GetWidth(); j++) {
            uint8_t r = img.GetR(ax + i, ay + j);
            uint8_t g = img.GetG(ax + i, ay + j);
            uint8_t b = img.GetB(ax + i, ay + j);
            uint8_t a = img.GetA(ax + i, ay + j);
            temp.SetColor(i, j, r, g, b, a);
        }
    }
    img = temp;

    return std::make_pair(ax, ay);
}

Image ImageUtil::Rotate(const Image &img, double angle) {
    double cosa = std::cos(angle);
    double sina = std::sin(angle);

    int width = std::ceil(img.GetWidth() * abs(cosa) + img.GetHeight() * abs(sina));
    int height = std::ceil(img.GetWidth() * abs(sina) + img.GetHeight() * abs(cosa));
    Image res(width, height);

    double sx, sy;
    angle = std::remainder(angle, 2 * MathUtil::PI);
    if (angle < 0) angle += 2 * MathUtil::PI;
    if (angle < 0.5 * MathUtil::PI) {
        sx = img.GetWidth() * sina;
        sy = 0;
    } else if (angle < 1.0 * MathUtil::PI) {
        sx = height;
        sy = img.GetWidth() * -cosa;
    } else if (angle < 1.5 * MathUtil::PI) {
        sx = img.GetHeight() * -cosa;
        sy = width;
    } else {
        sx = 0;
        sy = img.GetHeight() * -sina;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double dx = i + 0.5 - sx;
            double dy = j + 0.5 - sy;
            double tx = dx * cosa + dy * sina;
            double ty = dx * -sina + dy * cosa;
            double u = tx / img.GetHeight();
            double v = ty / img.GetWidth();
            uint8_t r, g, b, a;
            img.SampleAt(u, v, r, g, b, a);
            res.SetColor(i, j, r, g, b, a);
        }
    }

    Adjust(res);
    return res;
}

Image ImageUtil::Scale(const Image &img, double sx, double sy) {
    int width = std::ceil(img.GetWidth() * sy);
    int height = std::ceil(img.GetHeight() * sx);
    Image res(width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double u = (i + 0.5) / height;
            double v = (j + 0.5) / width;
            uint8_t r, g, b, a;
            img.SampleAt(u, v, r, g, b, a);
            res.SetColor(i, j, r, g, b, a);
        }
    }

    return res;
}

Image ImageUtil::ShearX(const Image &img, double dx) {
    int width = std::ceil(img.GetWidth() + std::abs(dx));
    int height = img.GetHeight();
    Image res(width, height);
    double sy = (dx > 0 ? 0 : -dx);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double u = (i + 0.5) / img.GetHeight();
            double v = (j + 0.5 - u * dx - sy) / img.GetWidth();
            uint8_t r, g, b, a;
            img.SampleAt(u, v, r, g, b, a);
            res.SetColor(i, j, r, g, b, a);
        }
    }

    Adjust(res);
    return res;
}

Image ImageUtil::ShearY(const Image &img, double dy) {
    int width = img.GetWidth();
    int height = std::ceil(img.GetHeight() + std::abs(dy));
    Image res(width, height);
    double sx = (dy > 0 ? 0 : -dy);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double v = (j + 0.5) / img.GetWidth();
            double u = (i + 0.5 - v * dy - sx) / img.GetHeight();
            uint8_t r, g, b, a;
            img.SampleAt(u, v, r, g, b, a);
            res.SetColor(i, j, r, g, b, a);
        }
    }

    Adjust(res);
    return res;
}

Image ImageUtil::MirrorX(const Image &img) {
    Image res = img;
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t r = img.GetR(img.GetHeight() - i - 1, j);
            uint8_t g = img.GetG(img.GetHeight() - i - 1, j);
            uint8_t b = img.GetB(img.GetHeight() - i - 1, j);
            uint8_t a = img.GetA(img.GetHeight() - i - 1, j);
            res.SetColor(i, j, r, g, b, a);
        }
    }
    return res;
}

Image ImageUtil::MirrorY(const Image &img) {
    Image res = img;
    for (int i = 0; i < img.GetHeight(); i++) {
        for (int j = 0; j < img.GetWidth(); j++) {
            uint8_t r = img.GetR(i, img.GetWidth() - j - 1);
            uint8_t g = img.GetG(i, img.GetWidth() - j - 1);
            uint8_t b = img.GetB(i, img.GetWidth() - j - 1);
            uint8_t a = img.GetA(i, img.GetWidth() - j - 1);
            res.SetColor(i, j, r, g, b, a);
        }
    }
    return res;
}