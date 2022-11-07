#include <iostream>
#include <iomanip>
#include <cmath>

template <typename T>
void sum(size_t N) {
    T res = 1;
    std::cout << std::setw(3) << 0 << " | " << std::setprecision(10) << res << "\n";
    for (size_t i = 1; i <= N; i++) {
        res += static_cast<T>(1) / pow(2, i);
        std::cout << std::setw(3) << i << " | " << std::setprecision(10) << res << "\n";
    }
}

int main() {
    sum<float>(100);

    return 0;
}
