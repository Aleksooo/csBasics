#include <iostream>

template <typename T, size_t dim = 2>
class PendulumEquation {
private:
    T OMEGA;
    typedef State<T, dim> State;

public:
    PendulumEquation() : OMEGA(1.0) {}
    PendulumEquation(T OMEGA_) : OMEGA(OMEGA_) {}

    State dfdt(State curr_state, T t) {
        return {State(std::array<T, dim> {curr_state[1], -OMEGA * sin(curr_state[0])})};
    }
};

template <typename T, size_t dim = 2>
class FrictionPendulumEquation {
private:
    T OMEGA, GAMMA;
    typedef State<T, dim> State;

public:
    FrictionPendulumEquation() : OMEGA(1.0), GAMMA(0.1) {}
    FrictionPendulumEquation(T OMEGA_, T GAMMA_) : OMEGA(OMEGA_), GAMMA(GAMMA_) {}

    State dfdt(State curr_state, T t) {
        return {State(std::array<T, dim> {curr_state[1], -2 * GAMMA * curr_state[1] - OMEGA * OMEGA * sin(curr_state[0])})};
    }
};

template <typename T, size_t dim = 2>
class ExternalPendulumEquation {
private:
    T OMEGA, GAMMA, A, BIG_OMEGA;
    typedef State<T, dim> State;

public:
    ExternalPendulumEquation() : OMEGA(1.0), GAMMA(0.1), A(1.0), BIG_OMEGA(0.5) {}
    ExternalPendulumEquation(T OMEGA_, T GAMMA_, T A_, T BIG_OMEGA_) : OMEGA(OMEGA_), GAMMA(GAMMA_), A(A_), BIG_OMEGA(BIG_OMEGA_) {}

    State dfdt(State curr_state, T t) {
        return {State(std::array<T, dim> {
            curr_state[1],
            -2 * GAMMA * curr_state[1] - OMEGA * OMEGA * sin(curr_state[0]) + A * cos(BIG_OMEGA * t)
        })};
    }
};

template <typename T, size_t dim = 4>
class DoublePendulumEquation {
private:
    T M1, L1, M2, L2;
    typedef State<T, dim> State;

public:
    DoublePendulumEquation() : M1(1.0), L1(1.0), M2(1.0), L2(1.0) {}
    DoublePendulumEquation(T M1_, T L1_, T M2_, T L2_) : M1(M1_), L1(L1_), M2(M2_), L2(L2_) {}

    State dfdt(State curr_state, T t) {
        T mu = M2 / (M1 + M2);
        T l = L1 / L2;
        T delta = curr_state[0] - curr_state[2];

        T K = 1 / (1 - mu * std::pow(std::cos(delta), 2));
        T A1 = g * (mu * std::cos(delta) * std::sin(curr_state[2]) - std::sin(curr_state[0])) / L1;
        T A2 = curr_state[1] * curr_state[1] * mu * std::sin(2 * delta) / 2;
        T A3 = curr_state[3] * curr_state[3] * mu * std::sin(delta) / l;

        T B1 = g * (std::cos(delta) * std::sin(curr_state[0]) - std::sin(curr_state[2])) / L2;
        T B2 = curr_state[1] * curr_state[1] * l * std::sin(delta);
        T B3 = curr_state[3] * curr_state[3] * mu * std::sin(2 * delta) / 2;
        return {State(std::array<T, dim> {
            curr_state[1],
            K * (A1 - A2 - A3),
            curr_state[3],
            K * (B1 + B2 + B3)
        })};
    }
};

template <typename T, size_t dim = 2>
class KapitzaPendulumEquation {
private:
    T L, A, nu;
    typedef State<T, dim> State;

public:
    KapitzaPendulumEquation() : L(1.0), A(0.2), nu(1.0) {}
    KapitzaPendulumEquation(T L_, T A_, T nu_) : L(L_), A(A_), nu(nu_) {}

    State dfdt(State curr_state, T t) {
        return {State(std::array<T, dim> {
            curr_state[1],
            -(A * nu * nu * std::cos(nu * t) + g) * std::sin(curr_state[0]) / L
        })};
    }
};
