#include <iostream>

template <typename State, typename Eq>
class EulerSolver {
public:
    void make_step(State& curr_state, Eq& eq, typename State::my_type dt, size_t step_id=0) {
        auto f = eq.dfdt(curr_state, step_id * dt);
        curr_state += f * dt;
    }
};

template <typename State, typename Eq>
class HeunSolver {
public:
    void make_step(State& curr_state, Eq& eq, typename State::my_type dt, size_t step_id=0) {
        auto f = eq.dfdt(curr_state, step_id * dt);
        curr_state += f * dt;
        auto f_inter = eq.dfdt(curr_state, step_id * dt);
        curr_state += (f + f_inter) * dt / 2.0;
    }
};


template <typename State, typename Eq>
class RungeKuttaSolver {
public:
    void make_step(State& curr_state, Eq& eq, typename State::my_type dt, size_t step_id=0) {
        auto k1 = eq.dfdt(curr_state, step_id * dt);
        auto k2 = eq.dfdt(curr_state + k1 * dt * 0.5, (step_id + 0.5) * dt);
        auto k3 = eq.dfdt(curr_state + k2 * dt * 0.5, (step_id + 0.5) * dt);
        auto k4 = eq.dfdt(curr_state + k3 * dt, (step_id + 1.0) * dt);

        curr_state += (k1 + k2 * 2 + k3 * 2 + k4) * dt / 6.0;
    }
};
