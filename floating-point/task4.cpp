#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <cmath>

float my_expf(float min, float max, size_t N, bool reverse=false) {
    float res = 0;
    float dx = (max - min) / (N - 1);
    if (!reverse) {
        for (size_t i = 0; i < N - 1; i++) {
            res += (expf(-powf(i * dx, 2)) + expf(-powf((i + 1) * dx, 2))) / 2 * dx;
        }
    } else {
        for (int i = N-1; i > 0; i--) {
            res += (expf(-powf(i * dx, 2)) + expf(-powf((i - 1) * dx, 2))) / 2 * dx;
        }
    }

    return res;
}

int main() {
    // size_t N = 2;

    for (size_t i_max = 1; i_max < 5; i_max++) {
        float min = 0, max = (1 << i_max);
        std::cout << "from: " << min << "; to: " << max << "\n\n";
        for (size_t i = 1; i < 10; i++) {
            // std::cout << std::setw(10) << "target:" << " : ";
            // std::cout << std::setprecision(15) << sqrt(M_PI) / 2 << "\n";
            // std::cout << std::setw(10) << "forward:" << " : ";
            // std::cout << std::setprecision(15) << my_expf(min, max, N);
            // std::cout << " | delta: " << abs(my_expf(min, max, N) - sqrt(M_PI) / 2) << "\n";
            // std::cout << std::setw(10) << "reverse:" << " : ";
            // std::cout << std::setprecision(15) << my_expf(min, max, N, true);
            // std::cout << " | delta: " << abs(my_expf(min, max, N, true) - sqrt(M_PI) / 2) << "\n";

            std::cout << "2^-" << i << "\n";
            std::cout << "delta | " << my_expf(min, max, (1 << i) + 1) * 2 / sqrt(M_PI) - 1 << "\n";
        }
        std::cout << "\n\n";
    }

    return 0;
}
