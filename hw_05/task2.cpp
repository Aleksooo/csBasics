#include <iostream>
#include <iomanip>

template <typename T>
void natural_series(size_t begin, size_t end, size_t step, bool inverse=false) {
    T res = 0;
    if (inverse) {
        for (size_t i = end; i >= begin; i--) {
            if (static_cast<T>(1) / i < 0) {
                std::cout << "minus!!!";
                exit(1);
            }
            res += static_cast<T>(1) / i;
            if (i % step == 0 || i == 1) {
                std::cout << std::setw(5) << i << " | " << res << "\n";
            }
        }
    } else {
        for (size_t i = begin; i <= end; i++) {
            if (static_cast<T>(1) / i < 0) {
                std::cout << "minus!!!";
                exit(1);
            }
            res += static_cast<T>(1) / i;
            if (i % step == 0 || i == 1) {
                std::cout << std::setw(5) << i << " | " << res << "\n";
            }
        }
    }
}

int main() {
    natural_series<float>(1, 20'000'000, 4'000'000);
    std::cout << "\n";
    natural_series<float>(1, 20'000'000, 4'000'000, true);

    return 0;
}
