double const pi = 3.14;
double const g = 9.81;

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cmath>
#include "../libs/json.hpp"
#include "State.h"
#include "Equation.h"
#include "Solver.h"
using json = nlohmann::json;

// typedef PendulumEquation<double> EQ_TYPE;
// typedef FrictionPendulumEquation<double> EQ_TYPE;
// typedef ExternalPendulumEquation<double> EQ_TYPE;
typedef DoublePendulumEquation<double> EQ_TYPE;
// typedef KapitzaPendulumEquation<double> EQ_TYPE;

typedef State<double, 4> STATE_TYPE;
typedef EulerSolver<STATE_TYPE, EQ_TYPE> EULER_SOLVER_TYPE;
typedef HeunSolver<STATE_TYPE, EQ_TYPE> HEUN_SOLVER_TYPE;
typedef RungeKuttaSolver<STATE_TYPE, EQ_TYPE> RK_SOLVER_TYPE;


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Wrong amount of parametrs!!!" << std::endl;
        return -1;
    }

//  ***** Reading .json config *****
    std::string path("configs/");
    path.append(argv[1]);
    std::ifstream f(path);
    json data = json::parse(f);

    // all other parametrs of pendulum
    // double OMEGA = data["OMEGA"];
    // double GAMMA = data["GAMMA"];
    // double A = data["A"];
    // double BIG_OMEGA = data["BIG_OMEGA"];

    double t_left = 2 * pi * data["left"].get<double>(); // left bound
    double t_right = 2 * pi * data["right"].get<double>(); // right bound
    size_t N = data["N"]; // number of points
    double dt = (t_right - t_left) / (N - 1); // step


//  ***** Creating problem... *****
    // EQ_TYPE eq(data["OMEGA"].get<double>(), data["OMEGA"].get<double>(), data["A"].get<double>(), data["BIG_OMEGA"].get<double>());
    EQ_TYPE eq(data["M1"].get<double>(), data["L1"].get<double>(), data["M2"].get<double>(), data["L2"].get<double>());
    // EQ_TYPE eq(data["L"].get<double>(), data["A"].get<double>(), data["nu"].get<double>());

    // STATE_TYPE state(std::array<double, 2> {data["x0"], data["v0"]});
    STATE_TYPE state(std::array<double, 4> {data["a0"], data["va0"], data["b0"], data["vb0"],});
    // STATE_TYPE state(std::array<double, 2> {data["phi0"].get<double>(), data["omega0"].get<double>()});

    // EULER_SOLVER_TYPE solver;
    // HEUN_SOLVER_TYPE solver;
    RK_SOLVER_TYPE solver;

//  ***** Solving problem! *****
    std::cout << state << "\n";
    for (size_t i = 1; i < N; i++) {
        solver.make_step(state, eq, dt, i-1);
        std::cout << state << "\n";
    }

    return 0;
}
