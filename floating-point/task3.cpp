#include <iostream>
#include <iomanip>
#include <cmath>

size_t fact(size_t n) {
    return (n == 1 || n == 0) ? 1 : n * fact(n-1);
}

template <typename T>
T my_sin(T x, size_t N, bool reverse = false) {
    T res = 0;
    if (!reverse) {
        bool flag = true;
        for(size_t i = 1; i < 2 * N; i += 2) {
            if (flag) {
                res += pow(x, i) / fact(i);
            } else {
                res -= pow(x, i) / fact(i);
            }

            flag = !flag;
        }
    } else {
        bool flag = ((N - 1) % 2 == 0) ? true : false;
        for(int i = 2 * N - 1; i >= 1; i -= 2) {
            if (flag) {
                res += pow(x, i) / fact(i);
            } else {
                res -= pow(x, i) / fact(i);
            }

            flag = !flag;
        }
    }

    return res;
}

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Wrong amount of parametrs!!!" << std::endl;
        return -1;
    }

    int left = std::atoi(argv[1]);
    int right = std::atoi(argv[2]);
    float step = std::atof(argv[3]);
    size_t N = std::atoi(argv[4]);

    std::cout << left << " " << right << " " << step << " " << N << "\n";
    std::cout << "# x\tf(x)\n";

    for (int i = left; i <= right; i++) {
        float x = i * step * 1.0;
        // std::cout << "x: " << x << "\tN: " << N << "\n";
        // // std::cout << std::setw(6) << "my_sin" << " | " << std::setprecision(15) << my_sin<float>(x, N, true) << "\n";
        // // std::cout << std::setw(6) << "sin" << " | " << std::setprecision(15) << sin(x) << "\n";
        // std::cout << std::setw(15) << "delta forward" << " | " << std::setprecision(15) << abs(sin(x) - my_sin(x, N))  << "\n";
        // std::cout << std::setw(15) << "delta reversed" << " | " << std::setprecision(15) << abs(sin(x) - my_sin(x, N, true))  << "\n";
        // std::cout << "\n";

        std::cout << x << "\t" << my_sin(x, N) << "\n";
    }

    // for (size_t i = 0; i < 10; i++) {
    //     std::cout << std::setw(2) << i << " | " << fact(i) << "\n";
    // }

    return 0;
}
